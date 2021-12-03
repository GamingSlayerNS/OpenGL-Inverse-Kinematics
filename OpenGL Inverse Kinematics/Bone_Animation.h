#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

class Bone_Animation
{
public:
	Bone_Animation();
	~Bone_Animation();

	void init();
	void update(float delta_time);
	glm::mat4 bone1_matrix(glm::mat4 bone1_mat);
	glm::mat4 bone2_matrix(glm::mat4 bone2_mat);
	glm::mat4 bone3_matrix(glm::mat4 bone3_mat);
	bool jacobian_IK();
	void get_jac_orientation();
	void reset();

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;	//Actually 4x3, but 3x3 matrix for the joint angles (vectors [1]-[3])
	std::vector<glm::vec4> colors;
	std::vector<glm::mat4> rotate_matrix;
	std::vector<glm::vec3> jacobian_vectors;		//9x3 matrix
	float step_size = 0.001;

	glm::vec3 root_position;
	glm::vec3 bone1_position;
	glm::vec3 bone2_position;
	glm::vec3 bone3_position;
	glm::vec3 bone1_end;
	glm::vec3 bone2_end;
	glm::vec3 endEffector_position;
	glm::vec3 target_position;

	glm::mat4 bone1Matrix;							//save bone1_mat for jacobian calculations
	glm::mat4 bone2Matrix;							//save bone2_mat for jacobian calculations
	glm::mat4 bone3Matrix;							//save bone3_mat for jacobian calculations
};

