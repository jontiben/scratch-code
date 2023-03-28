def dot_product(v, w):
	# Returns the dot product of two vectors
	return v[0] * w[0] + v[1] * w[1]

def closest_point_coords(segment: tuple, point: tuple) -> tuple:
    # Takes an input of form:
    # (((float, float), (float, float)), (float, float))
    # (((x_1,   y_1  ), (x_2,   y_2  )), (x_p,   y_p  ))
    # Where _1 and _2 are points on segment, and _p are the point

    # Returns a tuple of (float [x], float [y]) representing the closest point on the
    # line to the input point.

    x_1, y_1 = segment[0]
    x_2, y_2 = segment[1]
    x_p, y_p = point

    p_1_vector = (x_p - x_1, y_p - y_1)
    seg_vector = (x_2 - x_1, y_2 - y_1)

    scalar_projection = dot_product(p_1_vector, seg_vector) / dot_product(seg_vector, seg_vector)
    clamping = max(0, (min(1, scalar_projection))) # Point must be on line segment

    return (x_1 + clamping * seg_vector[0], y_1 + clamping * seg_vector[1])


if __name__ == "__main__":
	segment = ((0.0, 0.0), (5.0, 3.0))
	point = ((1.0, 0.0))
	print(f"Closest point to {point} on {segment}: {closest_point_coords(segment, point)}")


