/**
 * Header file for sersic profile implementation
 *
 * ICRAR - International Centre for Radio Astronomy Research
 * (c) UWA - The University of Western Australia, 2016
 * Copyright by UWA (in the framework of the ICRAR)
 * All rights reserved
 *
 * Contributed by Rodrigo Tobar
 *
 * This file is part of libprofit.
 *
 * libprofit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprofit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libprofit.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _SERSIC_H_
#define _SERSIC_H_

#include "sersic_like.h"

namespace profit
{

class SersicProfile : public SersicLikeProfile {

protected:
	void initial_calculations();
	void subsampling_params(double x, double y, unsigned int &res, unsigned int &max_rec);
	double get_pixel_scale();
	double get_rscale();
	double get_lumtot(double r_box);
	double adjust_rscale_switch();
	double adjust_rscale_max();
	double adjust_acc();
	eval_function_t get_evaluation_function();

public:

	SersicProfile();

	/* General parameters */
	double re;
	double nser;

	/* Rescale flux or not */
	bool rescale_flux;

	/* These are internally calculated profile init */
	double _bn;
	double _rescale_factor;

};

} /* namespace profit */

#endif /* _SERSIC_H_ */
