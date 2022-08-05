#include <PeleLM.H>
#include <pelelm_prob.H>
#include <PMF.H>

extern "C" {
void
amrex_probinit(
  const int* /*init*/,
  const int* /*name*/,
  const int* /*namelen*/,
  const amrex_real* problo /*problo*/,
  const amrex_real* probhi /*probhi*/)
{
  amrex::ParmParse pp("prob");

  pp.query("P_mean", PeleLM::prob_parm->P_mean);
  pp.query("standoff", PeleLM::prob_parm->standoff);
  pp.query("pertmag", PeleLM::prob_parm->pertmag);

  pp.query("jet_vel", PeleLM::prob_parm->jet_vel);
  // The cells are divided by this value when prescribing the jet inlet
  pp.get("jet_dia", PeleLM::prob_parm->jet_dia);
  pp.get("part_mean_dia", PeleLM::prob_parm->part_mean_dia);
  pp.query("part_stdev_dia", PeleLM::prob_parm->part_stdev_dia);
  pp.get("part_temp", PeleLM::prob_parm->part_temp);
  pp.query("mass_flow_rate", PeleLM::prob_parm->mass_flow_rate);
  pp.get("spray_angle_deg", PeleLM::prob_parm->spread_angle);
  std::vector<amrex::Real> in_Y_jet(SPRAY_FUEL_NUM, 0.);
  in_Y_jet[0] = 1.;
  pp.queryarr("jet_mass_fracs", in_Y_jet);
  amrex::Real sumY = 0.;
  for (int spf = 0; spf < SPRAY_FUEL_NUM; ++spf) {
    PeleLM::prob_parm->Y_jet[spf] = in_Y_jet[spf];
    sumY += in_Y_jet[spf];
  }
  if (std::abs(sumY - 1.) > 1.E-8) {
    amrex::Abort("'jet_mass_fracs' must sum to 1");
  }
  // Convert to radians
  PeleLM::prob_parm->spray_angle *= M_PI / 180.;
  for (int dir = 0; dir < AMREX_SPACEDIM; ++dir) {
    PeleLM::prob_parm->jet_cent[dir] =
      problo[dir] + 0.5 * (probhi[dir] - problo[dir]);
    PeleLM::prob_parm->jet_norm[dir] = 0.;
  }
  int lowD = AMREX_SPACEDIM - 1;
  PeleLM::prob_parm->jet_cent[lowD] = problo[lowD];
  PeleLM::prob_parm->jet_norm[lowD] = 1.;
}
}
