
#include "SprayParticles.H"
#include <AMReX_Particles.H>
#include <pelelm_prob.H>

bool
SprayParticleContainer::injectParticles(
  Real time,
  Real dt,
  int nstep,
  int lev,
  int finest_level,
  ProbParm const& prob_parm)
{
  amrex::ignore_unused(time, dt, nstep, lev, finest_level, prob_parm);
  return false;
}

void
SprayParticleContainer::InitSprayParticles(ProbParm const& prob_parm)
{
  amrex::ignore_unused(prob_parm);
}
