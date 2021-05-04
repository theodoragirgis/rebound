/**
 * @file 	integrator_whfast.h
 * @brief 	Interface for numerical particle integrator
 * @author 	Hanno Rein <hanno@hanno-rein.de>
 * 
 * @section 	LICENSE
 * Copyright (c) 2015 Hanno Rein, Daniel Tamayo
 *
 * This file is part of rebound.
 *
 * rebound is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rebound is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rebound.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _INTEGRATOR_WHFAST_H
#define _INTEGRATOR_WHFAST_H

#include "rebound.h"

void reb_integrator_whfast_part1(struct reb_simulation* r);		///< Internal function used to call a specific integrator
void reb_integrator_whfast_part2(struct reb_simulation* r);		///< Internal function used to call a specific integrator
void reb_integrator_whfast_synchronize(struct reb_simulation* r);	///< Internal function used to call a specific integrator
void reb_whfast_kepler_solver(const struct reb_simulation* const r, struct reb_particle* const restrict p_j, const double M, unsigned int i, double _dt);   ///< Internal function (Main WHFast Kepler Solver)
void reb_whfast_calculate_jerk(struct reb_simulation* r);       ///< Calculates "jerk" term
void reb_whfast_interaction_step(struct reb_simulation* const r, const double _dt);///< Internal function
void reb_whfast_jump_step(const struct reb_simulation* const r, const double _dt); ///< Internal function
void reb_whfast_kepler_step(const struct reb_simulation* const r, const double _dt); ///< Internal function
void reb_whfast_com_step(const struct reb_simulation* const r, const double _dt); ///< Internal function
void reb_integrator_whfast_from_inertial(struct reb_simulation* const r);   ///< Internal function to the appropriate WHFast coordinates from inertial
void reb_integrator_whfast_to_inertial(struct reb_simulation* const r); ///< Internal function to move back from particular WHFast coordinates to inertial
void reb_integrator_whfast_reset(struct reb_simulation* r);		///< Internal function used to call a specific integrator
int reb_integrator_whfast_init(struct reb_simulation* const r);    ///< Internal function to check errors and allocate memory if needed

#endif
