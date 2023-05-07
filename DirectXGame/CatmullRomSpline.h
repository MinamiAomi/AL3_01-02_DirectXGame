#pragma once
#include "MathUtils.h"
#include <vector>

class CatmullRomSpline {
public:
	/// <summary>
	/// 制御点を追加
	/// </summary>
	/// <param name="controlPoint">制御点</param>
	void AddControlPoint(const Vector3& controlPoint) { m_controlPoints.emplace_back(controlPoint); }
	/// <summary>
	/// 複数の制御点を追加
	/// </summary>
	/// <param name="controlPoints">制御点配列</param>
	void AddControlPoints(const std::vector<Vector3>& controlPoints);
	/// <summary>
	/// 制御点をクリア
	/// </summary>
	void ClearControlPoint() { m_controlPoints.clear(); }
	/// <summary>
	/// 制御点の数
	/// </summary>
	/// <returns></returns>
	size_t GetControlPointCount() const { return m_controlPoints.size(); }
	/// <summary>
	/// 制御点の参照を返す
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	Vector3& GetControlPointRef(size_t i) { return m_controlPoints[i]; }
	/// <summary>
	/// <para>  ループ時には制御点数と同じ </para>
	/// <para>  非ループ時には制御点ー１ </para>
	/// </summary>
	size_t GetSectionCount() const;
	/// <summary>
	/// ループをするか
	/// </summary>
	/// <param name="isLoop"></param>
	void SetIsLoop(bool isLoop) { m_isLoop = isLoop; }

	Vector3 ComputePoint(float t, size_t section);
	std::vector<Vector3> ComputePoints(size_t pointCount);

	static inline Vector3 Calc(float t, const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3) {
		return 0.5f *
		       ((-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t +
		        (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t + 
				(-p0 + p2) * t + 
				2.0f * p1);
	}

private:
	std::vector<Vector3> m_controlPoints;
	bool m_isLoop = false;
};
