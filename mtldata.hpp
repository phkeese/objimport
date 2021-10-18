#pragma once
#include "objdatatypes.hpp"
#include <map>
#include <string>
#include <vector>

/**
 * Material Template Library Data
 */

namespace objimport {

struct Material {
	inline Material(std::string name,			   //
					Vector3 ambient = {0, 0, 0},   //
					Vector3 diffuse = {1, 1, 1},   //
					Vector3 specular = {0, 0, 0},  //
					float specular_exponent = 0.0, //
					float transparency = 0.0,	   //
					float refraction = 0.0,		   //
					int illumination = 0		   //
					)
		: name{name}, ambient{ambient}, diffuse{diffuse}, specular{specular},
		  specular_exponent{specular_exponent}, transparency{transparency},
		  refraction{refraction}, illumination{illumination} {}

	std::string name;
	Vector3 ambient;		 // Ka, ambient color
	Vector3 diffuse;		 // Kd, diffuse color
	Vector3 specular;		 // Ks, specular color
	float specular_exponent; // Ns, strength of specular highlight
	float transparency;		 // Tr or 1 - d, transparency
	float refraction;		 // Ni, index of refraction
	int illumination;		 // illum, illumination mode
};

struct MTLData {
	MTLData();

	// Add a material and return the index to it
	index add_material(std::string name, Material m);

	// Retrieve material by name
	Material operator[](std::string name);
	// Retrieve material by index
	Material operator[](index i);

	std::map<std::string, index> material_indices;
	std::vector<Material> materials;
};

} // namespace objimport
