#include "CCapsule.h"

tVector2D ClosestPointOnALine( tVector2D start, tVector2D end, tVector2D testPoint)
{
	tVector2D ClosestPoint;

	// Find vector from the Start point to the endpoint
	tVector2D C = end - start;

	float length = Vector2DLength(C);
	tVector2D N = C / length;

	// Find the vector from the Start Point to the Test Point
	tVector2D V = testPoint - start;

	// Find the ratio
	float D = DotProduct(N, V);//(DotProduct(V,C) / DotProduct(C,C));

	// Find the Closest Point
	// Start + (Vector to the End * The Ratio)
	ClosestPoint = start + (N * D);


	if( D < 0)
		ClosestPoint = start;
	else if( D > length)
		ClosestPoint = end;

	return ClosestPoint;
}
