#pragma once

#include <string>
#include <vector>

static const double meters_per_degree = 111000.0f;

class SpatialHash
{
private:
	double cell_size_meters;
	double cell_size_degrees;

private:
	SpatialHash() {}
	SpatialHash(SpatialHash&) {}

public:
	explicit SpatialHash(double cell_size_metres);
	std::string ComputeHash(double longitude, double latitude);
	std::vector<std::string> GetHashesForCellsInRange(double longitude, double latitude, double meters);
};

static double NearestMultiple(double N, double M);
static double DistanceInMeters(double long1, double lat1, double long2, double lat2);

inline static double DegreesToMeters(double degrees)
{
	return degrees * meters_per_degree;
}

inline static double MetersToDegrees(double meters)
{
	return meters / meters_per_degree;
}

