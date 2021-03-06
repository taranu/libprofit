/**
 * Utility routines for libprofit
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

/*
 * We use either GSL or R to provide the low-level
 * beta, gamma and pgamma and qgamma functions needed by some profiles.
 * If neither is given the compilation should fail
 */
#if defined(HAVE_GSL)
	#include <gsl/gsl_cdf.h>
	#include <gsl/gsl_sf_gamma.h>
#elif defined(HAVE_R)
	#define R_NO_REMAP
	#include <Rmath.h>
#else
	#error("No high-level library (GSL or R) provided")
#endif

namespace profit {

void add_images(double *dest, double *src,
                unsigned int width, unsigned int height) {

	for(unsigned int i=0; i != width*height; i++, dest++, src++) {
		*dest += *src;
	}

}

void copy_to(double *tgt_img, unsigned int tgt_w, unsigned int tgt_h,
             double *src_img, unsigned int src_w, unsigned int src_h,
             int pos_x, int pos_y) {

	unsigned int i, j, tgt_x, tgt_y;

	for(j=0; j!=src_h; j++) {

		/* Don't draw outside the boundaries of the full image */
		if( (int)j+pos_y < 0 ) {
			continue;
		}
		tgt_y = j + (unsigned int)pos_y;
		if( tgt_y >= tgt_h ) {
			break;
		}

		for(i=0; i!=src_w; i++) {

			/* Don't draw outside the boundaries of the full image */
			if( (int)i+pos_x < 0 ) {
				continue;
			}
			tgt_x = i + (unsigned int)pos_x;
			if( tgt_x >= tgt_w ) {
				break;
			}

			tgt_img[tgt_x + tgt_y*tgt_w] = src_img[i + j*src_w];
		}
	}

}


void normalize(double *image, unsigned int img_width, unsigned int img_height) {

	unsigned int i;
	unsigned int size = img_width * img_height;
	double sum = 0;

	double *in = image;
	for(i=0; i!=size; i++) {
		sum += *in;
		in++;
	}

	in = image;
	for(i=0; i!=size; i++) {
		*in /= sum;
		in++;
	}

}

/* GSL-based functions */
#if defined(HAVE_GSL)
double qgamma(double p, double shape) {
	return gsl_cdf_gamma_Pinv(p, shape, 1);
}

double pgamma(double q, double shape) {
	return gsl_cdf_gamma_P(q, shape, 1);
}

double gammafn(double x) {
	return gsl_sf_gamma(x);
}

double beta(double a, double b) {
	return gsl_sf_beta(a, b);
}

/* R-based functions -- get rid of simple R-exported names first */
#elif defined(HAVE_R)
#undef qgamma
#undef pgamma
#undef gammafn
#undef beta

double qgamma(double p, double shape) {
	return ::Rf_qgamma(p, shape, 1, 1, 0);
}

double pgamma(double q, double shape) {
	return ::Rf_pgamma(q, shape, 1, 1, 0);
}

double gammafn(double x) {
	return ::Rf_gammafn(x);
}

double beta(double a, double b) {
	return ::Rf_beta(a, b);
}

#endif

} /* namespace profit */
