def intersect_coords(segment_1: tuple, segment_2: tuple) -> (float, float):
	# Takes an input of form:
	# (((float, float), (float, float)), ((float, float), (float, float)))
	# (((x_1,   y_1  ), (x_2,   y_2  )), ((x_3,   y_3  ), (x_4,   y_4  )))
	# Where _1 and _2 are points on segment_1, and _3 and _4 are on segment_2

	# Returns (float [x], float [y]) if the segments intersect, else None 

	x_1, y_1 = segment_1[0] # Segment 1 point 1
	x_2, y_2 = segment_1[1] # Segment 1 point 2
	x_3, y_3 = segment_2[0] # Segment 2 point 1
	x_4, y_4 = segment_2[1] # Segment 2 point 2

	# Calculating slopes (m)
	slope_1 = (y_2 - y_1) / (x_2 - x_1)
	slope_2 = (y_4 - y_3) / (x_4 - x_3)

	# Calculating y-intercepts (b)
	y_int_1 = y_1 - (slope_1 * x_1)
	y_int_2 = y_3 - (slope_2 * x_3)

	# Convenience values
	y_int_diff = y_int_2 - y_int_1
	slope_diff = slope_1 - slope_2
	if slope_diff == 0: # Parallel lines
		return None

	# Calculating the intercept point of the two infinite lines
	x_int_point = y_int_diff / slope_diff
	y_int_point = slope_1 * y_int_diff / slope_diff + y_int_1

	# Checking to make sure that the intersection is within both line segments
	min_x = min(x_1, x_2, x_3, x_4)
	max_x = max(x_1, x_2, x_3, x_4)
	min_y = min(y_1, y_2, y_3, y_4)
	max_y = max(y_1, y_2, y_3, y_4)
	if x_int_point > min_x and x_int_point < max_x:
		if y_int_point > min_y and y_int_point < max_y:
			return (x_int_point, y_int_point)

	# Intersection out of bounds
	return None

if __name__ == "__main__":
	# demo
	segment_1 = ((2, 3), (5, 2))
	segment_2 = ((5, 1), (1, 4))
	print(intersect_coords(segment_1, segment_2))

