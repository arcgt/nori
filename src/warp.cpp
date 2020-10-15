/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/warp.h>
#include <nori/vector.h>
#include <nori/frame.h>

NORI_NAMESPACE_BEGIN

Vector3f Warp::sampleUniformHemisphere(Sampler *sampler, const Normal3f &pole) {
    // Naive implementation using rejection sampling
    Vector3f v;
    do {
        v.x() = 1.f - 2.f * sampler->next1D();
        v.y() = 1.f - 2.f * sampler->next1D();
        v.z() = 1.f - 2.f * sampler->next1D();
    } while (v.squaredNorm() > 1.f);

    if (v.dot(pole) < 0.f)
        v = -v;
    v /= v.norm();

    return v;
}

Point2f Warp::squareToUniformSquare(const Point2f &sample) {
    return sample;
}

float Warp::squareToUniformSquarePdf(const Point2f &sample) {
    return ((sample.array() >= 0).all() && (sample.array() <= 1).all()) ? 1.0f : 0.0f;
}

Point2f Warp::squareToUniformDisk(const Point2f &sample) { // uniform sampling of disk, following steps in ppt
    float r = sqrt(sample.x());
    float theta = 2 * M_PI * sample.y();
    return Point2f(r*cos(theta), r*sin(theta));
}

float Warp::squareToUniformDiskPdf(const Point2f &p) { // 1 / (pi*r^2), r = 1
    if (pow(p.norm(), 2) < 1) { // uniform density in Cartesian coordinate frame: if x^2 + y^2 < 1
        return INV_PI;
    }
    return 0;
}

Vector3f Warp::squareToUniformCylinder(const Point2f &sample) { //cylindrial to cartesian
    float phi = 2 * M_PI * sample.y();
    float wx = cos(phi);
    float wy = sin(phi);
    float wz = 2*sample.x() - 1; // range -1, 1
    return Vector3f(wx, wy, wz);
}

Vector3f Warp::squareToUniformSphereCap(const Point2f &sample, float cosThetaMax) { // map cylinder.z from [-1,1] to [cosThetaMax, 1]
    Vector3f cylinder = squareToUniformCylinder(sample);
    float wz = cosThetaMax + (cylinder.z() + 1) / 2 * (1-cosThetaMax);
    float r = sqrt(1 - pow(wz, 2));
    return Vector3f(r*cylinder.x(), r*cylinder.y(), wz);
}

float Warp::squareToUniformSphereCapPdf(const Vector3f &v, float cosThetaMax) { // 1 / (2 * pi * r * h), r = 1
    if (pow(v.norm(), 2) <= 1 && v.z() > cosThetaMax) {
      return (INV_PI / (2 * (1 - cosThetaMax)));
    }
    return 0;
}

Vector3f Warp::squareToUniformSphere(const Point2f &sample) { // using archimedes' hat-box theorem
    Vector3f cylinder = squareToUniformCylinder(sample);
    float r = sqrt(1 - pow(cylinder.z(), 2));
    return Vector3f(r*cylinder.x(), r*cylinder.y(), cylinder.z());
}

float Warp::squareToUniformSpherePdf(const Vector3f &v) { // 1 / (4*pi*r^2), r = 1
    if (pow(v.norm(), 2) <= 1) {
        return 0.25*INV_PI;
    }
    return 0;
}

Vector3f Warp::squareToUniformHemisphere(const Point2f &sample) { // if z < 0, z = -z using sampling of sphere
    Vector3f sphere = squareToUniformSphere(sample);
    return Vector3f(sphere.x(), sphere.y(), abs(sphere.z()));
}

float Warp::squareToUniformHemispherePdf(const Vector3f &v) { // 1 / (2*pi*r^2), r = 1
    if (v.norm() <= 1 && v.z() >= 0) {
        return 0.5*INV_PI;
    }
    return 0;
}

Vector3f Warp::squareToCosineHemisphere(const Point2f &sample) { // generate points uniformly on disk, project to surface of hemisphere
    Vector2f disk = squareToUniformDisk(sample);
    float wz = sqrt(1 - pow(disk.norm(), 2));
    return Vector3f(disk.x(), disk.y(), wz);
}

float Warp::squareToCosineHemispherePdf(const Vector3f &v) { // cos(theta) / pi, as given
    if (v.norm() <= 1 && v.z() >= 0) {
        return (v.z() / v.norm()) * INV_PI;
    }
    return 0;
}

Vector3f Warp::squareToBeckmann(const Point2f &sample, float alpha) { // solve by sampling 1D PDFs using inversion method, computing CDFs and inverting (lec slide 05 monte carlo, pg74)
    float phi = 2 * M_PI * sample.x();
    float theta = atan(sqrt(-pow(alpha, 2) * log(1 - sample.y())));
    return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

float Warp::squareToBeckmannPdf(const Vector3f &m, float alpha) { // pdf as given in the exercise
    float theta = acos(m.z() / m.norm());
    if (pow(m.norm(), 2) <= 1 && m.z() >= 0) {
        return (exp((-pow(tan(theta), 2)) / pow(alpha, 2)) / (M_PI * pow(alpha, 2) * pow(cos(theta), 3)));
    }
  	return 0;
}

Vector3f Warp::squareToUniformTriangle(const Point2f &sample) {
    float su1 = sqrtf(sample.x());
    float u = 1.f - su1, v = sample.y() * su1;
    return Vector3f(u,v,1.f-u-v);
}

NORI_NAMESPACE_END
