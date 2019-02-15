#pragma once

//%deps(estimate_imu_intrinsics)
#include "third_party/experiments/estimation/calibration/calibration_dataset.hh"
#include "third_party/experiments/estimation/calibration/estimate_imu_intrinsics.hh"
#include "third_party/experiments/geometry/types/unit_vector.hh"

//%deps(simple_geometry)
#include "third_party/experiments/viewer/primitives/simple_geometry.hh"
//%deps(ui2d)
#include "third_party/experiments/viewer/interaction/ui2d.hh"

namespace jet {
namespace filtering {

void visualize_imu_data_with_intrinsics(const estimation::calibration::ImuModel& imu_model,
                                        const estimation::calibration::CalibrationMeasurements& measurements,
                                        const geometry::UnitVector3& g_direction,
                                        const std::shared_ptr<viewer::SimpleGeometry> geo,
                                        const std::shared_ptr<viewer::Ui2d> ui2d);

void visualize_fwd_difference(const estimation::calibration::CalibrationMeasurements& measurements,
                              const std::shared_ptr<viewer::SimpleGeometry> geo,
                              const std::shared_ptr<viewer::Ui2d> ui2d);
}  // namespace filtering
}  // namespace jet