#include "CatmullRomSpline.h"
#include <algorithm>
#include <cassert>

void CatmullRomSpline::AddControlPoints(const std::vector<Vector3>& controlPoints) {
	m_controlPoints.insert(m_controlPoints.end(), controlPoints.begin(), controlPoints.end());
}

size_t CatmullRomSpline::GetSectionCount() const {
	if (m_isLoop) {
		return m_controlPoints.size();
	}
	return m_controlPoints.size() - 1;
}

Vector3 CatmullRomSpline::ComputePoint(float t, size_t section) {
	size_t sectionCount = GetSectionCount();
	assert(0 <= section && section < sectionCount);

	size_t p0 = 0, p1 = 0, p2 = 0, p3 = 0;

	if (m_isLoop) {
		p0 = ((section - 1) + sectionCount) % sectionCount;
		p1 = section;
		p2 = (section + 1) % sectionCount;
		p3 = (section + 2) % sectionCount;
	} 
	else {
		p0 = (section == 0) ? 0 : section - 1;
		p1 = section;
		p2 = section + 1;
		p3 = std::min(section + 2, sectionCount);
	}

	return Calc(
	    t, m_controlPoints[p0], m_controlPoints[p1], m_controlPoints[p2], m_controlPoints[p3]);
}

std::vector<Vector3> CatmullRomSpline::ComputePoints(size_t pointCount) {
	assert(pointCount >= m_controlPoints.size());

	std::vector<Vector3> result(pointCount);



	return std::vector<Vector3>();
}

