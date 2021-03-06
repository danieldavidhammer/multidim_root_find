#include <stdio.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_vector.h>
#include "five.h"

int five_f (const gsl_vector * x, void * params, gsl_vector * f) 
{

	double a = ((struct five_params *) params)->a;
	double b = ((struct five_params *) params)->b;
	double c = ((struct five_params *) params)->c;
	double d = ((struct five_params *) params)->d;
	double e = ((struct five_params *) params)->e;

	const double x0 = gsl_vector_get(x,0);
	const double x1 = gsl_vector_get(x,1);
	const double x2 = gsl_vector_get(x,2);
	const double x3 = gsl_vector_get(x,3);
	const double x4 = gsl_vector_get(x,4);

	const double y0 = a*x0*x1 + c*x4 + d*x4*x2;
	const double y1 = b*x1 -d*x4*x3 + e*x2;
	const double y2 = a*b*x2*x3 + d*b*x1 - x4*x2;
	const double y3 = b*d*x1*x2 - x2 + x3*x4;
	const double y4 = a*x2 - c*e*x4*x1;

	gsl_vector_set(f,0,y0);
	gsl_vector_set(f,1,y1);
	gsl_vector_set(f,2,y2);
	gsl_vector_set(f,3,y3);
	gsl_vector_set(f,4,y4);

	return GSL_SUCCESS;

}

int five_df (const gsl_vector *x, void * params, gsl_matrix * J) 
{	
	const double x0 = gsl_vector_get(x,0);
	const double x1 = gsl_vector_get(x,1);
	const double x2 = gsl_vector_get(x,2);
	const double x3 = gsl_vector_get(x,3);
	const double x4 = gsl_vector_get(x,4);

	double a = ((struct five_params *) params)->a;
	double b = ((struct five_params *) params)->b;
	double c = ((struct five_params *) params)->c;
	double d = ((struct five_params *) params)->d;
	double e = ((struct five_params *) params)->e;
	
	gsl_matrix_set(J,0,0, a*x1);
	gsl_matrix_set(J,0,1, a*x0);
	gsl_matrix_set(J,0,2, d*x4);
	gsl_matrix_set(J,0,3, 0);
	gsl_matrix_set(J,0,4, d*x2+c);

	gsl_matrix_set(J,1,0, 0);
	gsl_matrix_set(J,1,1, b);
	gsl_matrix_set(J,1,2, e);
	gsl_matrix_set(J,1,3, -d*x4);
	gsl_matrix_set(J,1,4, -d*x3);

	gsl_matrix_set(J,2,0, 0);
	gsl_matrix_set(J,2,1, b*d);
	gsl_matrix_set(J,2,2, a*b*x3-x4);
	gsl_matrix_set(J,2,3, a*b*x2);
	gsl_matrix_set(J,2,4, -x2);
	
	gsl_matrix_set(J,3,0, 0);
	gsl_matrix_set(J,3,1, b*d*x2);
	gsl_matrix_set(J,3,2, b*d*x1-1);
	gsl_matrix_set(J,3,3, x4);
	gsl_matrix_set(J,3,4, x3);

	gsl_matrix_set(J,4,0, 0);
	gsl_matrix_set(J,4,1, -c*e*x4);
	gsl_matrix_set(J,4,2, a);
	gsl_matrix_set(J,4,3, 0);
	gsl_matrix_set(J,4,4, -c*e*x1);

	return GSL_SUCCESS;
}


int five_fdf (const gsl_vector *x, void *params, gsl_vector * f, gsl_matrix * J) {

	const double x0 = gsl_vector_get(x,0);
	const double x1 = gsl_vector_get(x,1);
	const double x2 = gsl_vector_get(x,2);
	const double x3 = gsl_vector_get(x,3);
	const double x4 = gsl_vector_get(x,4);

	double a = ((struct five_params *) params)->a;
	double b = ((struct five_params *) params)->b;
	double c = ((struct five_params *) params)->c;
	double d = ((struct five_params *) params)->d;
	double e = ((struct five_params *) params)->e;
	
	const double y0 = a*x0*x1 + c*x4 + d*x4*x2;
	const double y1 = b*x1 -d*x4*x3 + e*x2;
	const double y2 = a*b*x2*x3 + d*b*x1 - x4*x2;
	const double y3 = b*d*x1*x2 - x2 + x3*x4;
	const double y4 = a*x2 - c*e*x4*x1;

	gsl_vector_set(f,0,y0);
	gsl_vector_set(f,1,y1);
	gsl_vector_set(f,2,y2);
	gsl_vector_set(f,3,y3);
	gsl_vector_set(f,4,y4);

	gsl_matrix_set(J,0,0, a*x1);
	gsl_matrix_set(J,0,1, a*x0);
	gsl_matrix_set(J,0,2, d*x4);
	gsl_matrix_set(J,0,3, 0);
	gsl_matrix_set(J,0,4, d*x2+c);

	gsl_matrix_set(J,1,0, 0);
	gsl_matrix_set(J,1,1, b);
	gsl_matrix_set(J,1,2, e);
	gsl_matrix_set(J,1,3, -d*x4);
	gsl_matrix_set(J,1,4, -d*x3);

	gsl_matrix_set(J,2,0, 0);
	gsl_matrix_set(J,2,1, b*d);
	gsl_matrix_set(J,2,2, a*b*x3-x4);
	gsl_matrix_set(J,2,3, a*b*x2);
	gsl_matrix_set(J,2,4, -x2);
	
	gsl_matrix_set(J,3,0, 0);
	gsl_matrix_set(J,3,1, b*d*x2);
	gsl_matrix_set(J,3,2, b*d*x1-1);
	gsl_matrix_set(J,3,3, x4);
	gsl_matrix_set(J,3,4, x3);

	gsl_matrix_set(J,4,0, 0);
	gsl_matrix_set(J,4,1, -c*e*x4);
	gsl_matrix_set(J,4,2, a);
	gsl_matrix_set(J,4,3, 0);
	gsl_matrix_set(J,4,4, -c*e*x1);
	
	return GSL_SUCCESS;
}
