#include "filtering/extract_data_from_log.hh"
#include "filtering/to_time_point.hh"

//%deps(jet_filter)
#include "third_party/experiments/estimation/jet/jet_filter.hh"
//%deps(jet_optimizer)
#include "third_party/experiments/estimation/jet/jet_optimizer.hh"
//%deps(estimate_imu_intrinsics)
#include "third_party/experiments/estimation/calibration/estimate_imu_intrinsics.hh"
//%deps(estimate_gravity_direction)
#include "third_party/experiments/estimation/calibration/estimate_gravity_direction.hh"

//%deps(simple_geometry)
#include "third_party/experiments/viewer/primitives/simple_geometry.hh"
//%deps(ui2d)
#include "third_party/experiments/viewer/interaction/ui2d.hh"
//%deps(window_3d)
#include "third_party/experiments/viewer/window_3d.hh"

#include "filtering/visualization/visualize_calibration.hh"

//%deps(log)
#include "third_party/experiments/logging/log.hh"

// - Validate reprojection of fiducial detection using the packaged calibration
// - Validate opencv calibration
// x - Estimate IMU intrinsics
// x - Estimate direction of gravity
// - 2D imageview

namespace jet {
namespace filtering {

namespace {

const bool visualize_imu_model = false;
const bool visualize_fiducial = true;
bool visualize() {
  return (visualize_imu_model || visualize_fiducial);
}

void setup() {
  if (visualize()) {
    const auto view = viewer::get_window3d("Calibration");
    view->set_continue_time_ms(1);
    const auto background = view->add_primitive<viewer::SimpleGeometry>();
    const geometry::shapes::Plane ground{jcc::Vec3::UnitZ(), 0.0};
    background->add_plane({ground, 0.1});
    background->flip();
  }
}

struct JetModel {
  estimation::calibration::ImuModel imu_model;
};

JetModel create_jet_model(const estimation::calibration::CalibrationMeasurements& cal_measurements) {
  std::vector<jcc::Vec3> imu_measurements;
  imu_measurements.reserve(cal_measurements.accel_meas.size());
  for (const auto& accel_meas : cal_measurements.accel_meas) {
    imu_measurements.push_back(accel_meas.measurement.observed_acceleration);
  }
  jcc::Success() << "[IMU]: Estimating intrinsics..." << std::endl;
  const auto imu_model = estimation::calibration::estimate_imu_intrinsics(imu_measurements);
  jcc::Success() << "[IMU]: Estimating sensor-frame direction of gravity..." << std::endl;
  const auto g_direction = estimate_gravity_direction(cal_measurements, imu_model, {});

  //
  // IMU Visualization
  //
  {
    jcc::Success() << "[IMU] Visualizing for validation..." << std::endl;
    if (visualize_imu_model) {
      const auto view = viewer::get_window3d("Calibration");
      const auto geo = view->add_primitive<viewer::SimpleGeometry>();
      const auto ui2d = view->add_primitive<viewer::Ui2d>();

      view->add_toggle_hotkey("visualize_imu_data", true, 'P');
      const auto view_cb = [geo, ui2d, imu_model, cal_measurements, g_direction](const bool visualize_imu_data) {
        if (visualize_imu_data) {
          visualize_imu_data_with_intrinsics(imu_model, cal_measurements, g_direction.direction, geo, ui2d);
        } else {
          visualize_fwd_difference(cal_measurements, geo, ui2d);
        }
      };
      view->add_toggle_callback("visualize_imu_data", view_cb);

      view_cb(view->get_toggle("visualize_imu_data"));
      view->spin_until_step();
    }
    jcc::Success() << "[IMU] Done Visualizing" << std::endl;
  }
  jcc::Success() << "[IMU] Done Calibration IMU" << std::endl;

  return JetModel{imu_model};
}

}  // namespace

void go() {
  jcc::Success() << "Preparing to calibrate" << std::endl;

  //
  // Grab the calibration data from the log
  //

  // const std::string path = "/jet/logs/calibration-log-feb9-2";
  // const std::string path = "/jet/logs/calibration-log-feb14-1/";
  const std::string path = "/jet/logs/jet-calibration-log-apr6-1/";
  // const TimeRange range{to_time_point(Timestamp(1554601590585857480)),
  // to_time_point(Timestamp(1554601623314842631))};
  const TimeRange range{};
  const ExtractionConfiguration default_cfg{};
  const auto cal_measurements = extract_data_from_log(path, range, default_cfg);

  const double total_time = estimation::to_seconds(cal_measurements.accel_meas.back().timestamp -
                                                   cal_measurements.accel_meas.front().timestamp);
  jcc::Success() << "Done reading log." << std::endl;

  if (total_time < 30.0) {
    jcc::Warning() << "Total time (" << total_time << " seconds) less than 30.0 sec" << std::endl;
  } else {
    jcc::Success() << "Total time: " << total_time << " seconds" << std::endl;
  }

  //
  // Set up the viewer
  //
  setup();

  jcc::Success() << "Calibrating..." << std::endl;

  //
  // Calibrate the IMU intrinsics
  //

  const auto jet_model = create_jet_model(cal_measurements);

  //
  // Calibrate camera->imu extrinsics
  //
  const auto view = viewer::get_window3d("Calibration");
  const auto geo = view->add_primitive<viewer::SimpleGeometry>();
  const auto ui2d = view->add_primitive<viewer::Ui2d>();

  jcc::Success() << "[Camera] Validating fiducial measurements" << std::endl;
  ImageStream image_stream(path, range);
  jcc::Success() << "[Camera] Parsing image stream" << std::endl;

  while (true) {
    const auto image = image_stream.next();
    if (!image) {
      break;
    }
    ui2d->add_image(image->measurement, 1.0);
    ui2d->flip();
    view->spin_until_step();
  }
  jcc::Success() << "Done." << std::endl;
}

}  // namespace filtering
}  // namespace jet

int main() {
  jet::filtering::go();
}