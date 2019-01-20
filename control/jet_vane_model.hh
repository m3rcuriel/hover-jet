#pragma once

#include <cmath>

#include "third_party/experiments/eigen.hh"
#include "third_party/experiments/sophus.hh"

#include "control/wrench.hh"

namespace jet {
namespace control {

namespace detail {

// This expresses the transform from a zeroed vane to the jet vane unit's frame
SE3 compute_T_vane_unit_from_vane_default();

}  // namespace detail

// Vane static configuration
struct VaneConfiguration {
  // Vane default means the vane is pointed "down"; where servo_angle = 0.0 rad
  // TODO(Jake): replace this with the CAD
  SE3 T_vane_unit_from_vane_default = detail::compute_T_vane_unit_from_vane_default();
  double offset_vane_from_servo_rad = 0.0;

  double gear_ratio_servo_from_vane = 5.33;
  double max_servo_angle_rad = 1.116;
  double min_servo_angle_rad = -1.116;

  double vane_area_m2 = 20e-3 * 15e-3;

  // Dimensionless parameter for induced drag coefficient.
  // It relates the induced drag coefficient to the lift coefficient
  //    C_{Di} = (induced_drag_parameter) C_L^2
  // A value of 1/3 is a reasonable guess for a low-aspect ratio surface such as the vane.
  double induced_drag_param = 1.0 / 3.0;
  // Form & friction drag coefficient $C_{D0}$
  // The value of 0.05 is a conservative guess (likely overestimates the drag)
  double cd0 = 0.05;
};

// Jet static configuration
struct JetConfiguration {
  double v_exhaust_full_throttle_mps = 442.0;

  // Density of exhaust gas at 100 kPa, 900 K
  double rho_exhaust_kg_p_m3 = 0.39;
};

// Jet varying parameters
struct JetStatus {
  // Dimensionless: throttle ∈ [0, 1]
  double throttle;
};

// Compute the force generated by a vane, based on [1]
//
// @returns A wrench in the jet vane unit frame [2]
// Arguments:
//
// @param commanded_servo_angle_rad: The servo angle commanded to this vane/jet
// configuration
// @param jet_status The current state of the jet itself
// @param vane_cfg The fixed configuration of a servo
// @param jet_cfg The fixed configuration of the jet
//
// NOTE:
// [1]
// https://github.com/build-week/hover-jet/blob/feature/start-design-scripts/design-scripts/jet_vane_design.ipynb
// [2]
// https://cad.onshape.com/documents/eeb6df3e4d498ea4a465e30e/w/d46924a08f4a895c0ee963f0/e/28184c7ca5583574775fb500
Wrench vane_unit_wrench(const double commanded_servo_angle_rad,
                        const JetStatus& jet_status,
                        const VaneConfiguration& vane_cfg,
                        const JetConfiguration& jet_cfg);
}  // namespace control
}  // namespace jet