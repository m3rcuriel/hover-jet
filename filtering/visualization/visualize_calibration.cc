#include "filtering/visualization/visualize_calibration.hh"

namespace jet {
namespace filtering {

void visualize_imu_data_with_intrinsics(const estimation::calibration::ImuModel& imu_model,
                                        const estimation::calibration::CalibrationMeasurements& measurements,
                                        const geometry::UnitVector3& g_direction,
                                        const std::shared_ptr<viewer::SimpleGeometry> geo,
                                        const std::shared_ptr<viewer::Ui2d> ui2d) {
  geo->clear();
  ui2d->clear();
  const auto first = measurements.fiducial_meas.front().timestamp;

  viewer::LinePlotBuilder builder("IMU Readings");
  viewer::PlotRange range;
  range.x_min = 0.0;
  range.x_max = estimation::to_seconds(measurements.accel_meas.back().timestamp - first);
  builder.set_range(range);

  auto& imu_x = builder.make_subplot("imu_x", jcc::Vec4(1.0, 0.0, 0.0, 0.8), 0.5);
  auto& imu_y = builder.make_subplot("imu_y", jcc::Vec4(0.0, 1.0, 0.0, 0.8), 0.5);
  auto& imu_z = builder.make_subplot("imu_z", jcc::Vec4(0.0, 0.0, 1.0, 0.8), 0.5);

  for (const auto& accel_meas : measurements.accel_meas) {
    const jcc::Vec3 observed_acceleration = accel_meas.measurement.observed_acceleration;
    geo->add_point({observed_acceleration, jcc::Vec4(1.0, 0.1, 0.1, 1.0)});

    const jcc::Vec3 corrected = imu_model.apply_calibration(observed_acceleration);
    geo->add_point({corrected, jcc::Vec4(0.1, 1.0, 0.1, 1.0)});

    const double t = estimation::to_seconds(accel_meas.timestamp - first);

    imu_x << jcc::Vec2(t, corrected.x());
    imu_y << jcc::Vec2(t, corrected.y());
    imu_z << jcc::Vec2(t, corrected.z());
  }

  ui2d->add_lineplot(builder);
  ui2d->flip();

  constexpr double G_MPSS = 9.81;
  geo->add_sphere({jcc::Vec3::Zero(), G_MPSS});
  geo->add_line({jcc::Vec3::Zero(), g_direction.vector() * G_MPSS, jcc::Vec4(0.2, 0.7, 0.9, 1.0)});

  geo->flush();
}

void visualize_fwd_difference(const estimation::calibration::CalibrationMeasurements& measurements,
                              const std::shared_ptr<viewer::SimpleGeometry> geo,
                              const std::shared_ptr<viewer::Ui2d> ui2d) {
  geo->clear();
  ui2d->clear();
  const auto first = measurements.fiducial_meas.front().timestamp;

  viewer::LinePlotBuilder builder("Velocity");
  viewer::PlotRange range;
  range.x_min = 0.0;
  range.x_max = estimation::to_seconds(measurements.accel_meas.back().timestamp - first);
  builder.set_range(range);

  auto& vel_x = builder.make_subplot("vel_x", jcc::Vec4(1.0, 0.0, 0.0, 0.7), 0.4, true);
  auto& vel_y = builder.make_subplot("vel_y", jcc::Vec4(0.0, 1.0, 0.0, 0.7), 0.4, true);
  auto& vel_z = builder.make_subplot("vel_z", jcc::Vec4(0.0, 0.0, 1.0, 0.7), 0.4, true);
  auto& dt_plt = builder.make_subplot("dt", jcc::Vec4(0.0, 1.0, 1.0, 0.7), 0.4, false);

  for (std::size_t i = 1u; i < measurements.fiducial_meas.size(); ++i) {
    const auto prev = measurements.fiducial_meas.at(i - 1);
    const auto next = measurements.fiducial_meas.at(i);

    const auto fiducial_from_camera_0 = prev.measurement.T_fiducial_from_camera;
    const auto fiducial_from_camera_1 = next.measurement.T_fiducial_from_camera;

    const auto t0 = prev.timestamp;
    const auto t1 = next.timestamp;

    const SE3 camera_1_from_camera_0 = fiducial_from_camera_1.inverse() * fiducial_from_camera_0;

    const double dt = estimation::to_seconds(t1 - t0);
    const jcc::Vec3 dx_dt = camera_1_from_camera_0.translation() / dt;

    const double t = estimation::to_seconds(t0 - first);

    constexpr double MAX_DT_SEC = 0.2;
    dt_plt << jcc::Vec2(t, dt);
    if (dt < MAX_DT_SEC) {
      vel_x << jcc::Vec2(t, dx_dt.x());
      vel_y << jcc::Vec2(t, dx_dt.y());
      vel_z << jcc::Vec2(t, dx_dt.z());
    }
  }

  ui2d->add_lineplot(builder);
  ui2d->flip();

  geo->flush();
}

}  // namespace filtering
}  // namespace jet