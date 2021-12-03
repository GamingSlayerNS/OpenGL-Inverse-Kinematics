#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position  = {2.0f, 0.5f, 2.0f};
	bone1_position = {2.0f, 3.0f, 2.0f};
	bone2_position = {2.0f, 6.5f, 2.0f};
	bone3_position = {2.0f, 9.0f, 2.0f};
	endEffector_position = {0.0f, 0.0f, 0.0f};
	target_position = {3.0f, 8.0f, 3.0f};

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector =		//If these values are changed, change the reset values as well
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f}
	};

	colors = 
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.37f,0.12f,0.62f,1.0f},
		{0.0f,0.7f,0.7f,1.0f},
		{0.0f,0.7f,0.0f,1.0f}
	};
}

void Bone_Animation::update(float delta_time)
{
	rotate_matrix = std::vector<glm::mat4>();

	//Root Bone
	rotate_matrix.push_back(glm::mat4(1.0f));
	
	//Purple Bone
	glm::mat4 purpleMatrix =
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[1][0]), glm::vec3(1.0, 0.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[1][1]), glm::vec3(0.0, 1.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[1][2]), glm::vec3(0.0, 0.0, 1.0));
	rotate_matrix.push_back(purpleMatrix);

	//Cyan Bone
	glm::mat4 cyanMatrix =
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[2][0]), glm::vec3(1.0, 0.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[2][1]), glm::vec3(0.0, 1.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[2][2]), glm::vec3(0.0, 0.0, 1.0));
	rotate_matrix.push_back(cyanMatrix);

	//Green Bone
	glm::mat4 greenMatrix =
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[3][0]), glm::vec3(1.0, 0.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[3][1]), glm::vec3(0.0, 1.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_degree_vector[3][2]), glm::vec3(0.0, 0.0, 1.0));
	rotate_matrix.push_back(greenMatrix);
}

glm::mat4 Bone_Animation::bone1_matrix(glm::mat4 bone1_mat)
{
	bone1_mat =
		glm::translate(bone1_mat, glm::vec3(0.0f, -(scale_vector[1][1] / 2), 0.0f)) *		//move bone origin to bottom of bone from center of bone
		glm::translate(bone1_mat, bone1_position) *											//move bone according to root_position
		rotate_matrix[1] *																	//rotate bone according to rotation_degree_vector
		glm::translate(bone1_mat, glm::vec3(0.0f, scale_vector[1][1] / 2, 0.0f));			//move bone origin back to center of bone
	
	bone1_mat = glm::translate(bone1_mat, glm::vec3(0.0f, scale_vector[1][1] / 2, 0.0f));	//move to bone end
	bone1_end = bone1_mat[3];																//Assign bone1_end
	bone1_mat = glm::translate(bone1_mat, glm::vec3(0.0f, -(scale_vector[1][1] / 2), 0.0f));//undo move to end
	bone1_mat = glm::scale(bone1_mat, scale_vector[1]);										//scale bone according to scale_vector

	bone1Matrix = bone1_mat;
	return bone1_mat;
}

glm::mat4 Bone_Animation::bone2_matrix(glm::mat4 bone2_mat)
{
	bone2_mat =
		glm::translate(bone2_mat, glm::vec3(0.0f, -(scale_vector[2][1] / 2), 0.0f)) *		//move bone origin to bottom of bone from center of bone
		glm::translate(bone2_mat, glm::vec3(0.0f, -(scale_vector[1][1]), 0.0f)) *				//Apply bone1 -translation
		glm::translate(bone2_mat, bone2_position) *											//move bone according to root_position
		rotate_matrix[1] *																		//Apply bone1 rotation
		glm::translate(bone2_mat, glm::vec3(0.0f, scale_vector[1][1], 0.0f)) *					//Apply bone1 translation
		rotate_matrix[2] *																	//rotate bone according to rotation_degree_vector
		glm::translate(bone2_mat, glm::vec3(0.0f, scale_vector[2][1] / 2, 0.0f));			//move bone origin back to center of bone
		
	bone2_mat = glm::translate(bone2_mat, glm::vec3(0.0f, scale_vector[2][1] / 2, 0.0f));	//move to bone end
	bone2_end = bone2_mat[3];																//Assign bone2_end
	bone2_mat = glm::translate(bone2_mat, glm::vec3(0.0f, -(scale_vector[2][1] / 2), 0.0f));//undo move to end
	bone2_mat = glm::scale(bone2_mat, scale_vector[2]);										//scale bone according to scale_vector

	bone2Matrix = bone2_mat;
	return bone2_mat;
}

glm::mat4 Bone_Animation::bone3_matrix(glm::mat4 bone3_mat)
{
	bone3_mat =
		glm::translate(bone3_mat, glm::vec3(0.0f, -(scale_vector[3][1] / 2), 0.0f)) *		//move bone origin to bottom of bone from center of bone
		glm::translate(bone3_mat, glm::vec3(0.0f, -(scale_vector[2][1]), 0.0f)) *				//Apply bone2 -translation
		glm::translate(bone3_mat, glm::vec3(0.0f, -(scale_vector[1][1]), 0.0f)) *					//Apply bone1 -translation
		glm::translate(bone3_mat, bone3_position) *											//move bone according to root_position
		rotate_matrix[1] *																			//Apply bone1 rotation
		glm::translate(bone3_mat, glm::vec3(0.0f, scale_vector[1][1], 0.0f)) *						//Apply bone1 translation
		rotate_matrix[2] *																		//Apply bone2 rotation
		glm::translate(bone3_mat, glm::vec3(0.0f, scale_vector[2][1], 0.0f)) *					//Apply bone2 translation
		rotate_matrix[3] *																	//rotate bone according to rotation_degree_vector
		glm::translate(bone3_mat, glm::vec3(0.0f, scale_vector[3][1] / 2, 0.0f));			//move bone origin back to center of bone

	bone3_mat = glm::translate(bone3_mat, glm::vec3(0.0f, scale_vector[3][1] / 2, 0.0f));	//move to bone end
	endEffector_position = bone3_mat[3];													//Assign bone3's center position to endEffector's position
	bone3_mat = glm::translate(bone3_mat, glm::vec3(0.0f, -(scale_vector[3][1] / 2), 0.0f));//undo move to end
	bone3_mat = glm::scale(bone3_mat, scale_vector[3]);										//scale bone according to scale_vector

	bone3Matrix = bone3_mat;
	return bone3_mat;
}

bool Bone_Animation::jacobian_IK()
{
	if (glm::length(endEffector_position - target_position) > 0.1)	//1x10^-6 is how close the endeffector gets to the target position.
	{
		get_jac_orientation();															//Find jacobian matrix

		glm::vec3 goal_vec = target_position - endEffector_position;
		//Jacobian * target which is a 9x3 * 3x1, resulting in a 9x1 matrix with all the anlges to be inserted into rotation degree 3x3.
		//jacobian vectors are inserted as such:
		//rotation degree vector =
		//[6], [3], [0]
		//[7], [4], [1]
		//[8], [5], [2]
		rotation_degree_vector[1][2] += glm::dot(jacobian_vectors[0], goal_vec) * step_size;
		rotation_degree_vector[2][2] += glm::dot(jacobian_vectors[1], goal_vec) * step_size;
		rotation_degree_vector[3][2] += glm::dot(jacobian_vectors[2], goal_vec) * step_size;
		rotation_degree_vector[1][1] += glm::dot(jacobian_vectors[3], goal_vec) * step_size;
		rotation_degree_vector[2][1] += glm::dot(jacobian_vectors[4], goal_vec) * step_size;
		rotation_degree_vector[3][1] += glm::dot(jacobian_vectors[5], goal_vec) * step_size;
		rotation_degree_vector[1][0] += glm::dot(jacobian_vectors[6], goal_vec) * step_size;
		rotation_degree_vector[2][0] += glm::dot(jacobian_vectors[7], goal_vec) * step_size;
		rotation_degree_vector[3][0] += glm::dot(jacobian_vectors[8], goal_vec) * step_size;
		return true;
	}
	else
		return false;
}

void Bone_Animation::get_jac_orientation()
{
	glm::vec3 root_top = { root_position[0], root_position[1] + (scale_vector[0][1]/2), root_position[2] };
	glm::vec3 vec1 = glm::cross(glm::normalize(glm::vec3(bone1Matrix[2])), endEffector_position - root_top);
	glm::vec3 vec2 = glm::cross(glm::normalize(glm::vec3(bone2Matrix[2])), endEffector_position - bone1_end);
	glm::vec3 vec3 = glm::cross(glm::normalize(glm::vec3(bone3Matrix[2])), endEffector_position - bone2_end);
	glm::vec3 vec4 = glm::cross(glm::normalize(glm::vec3(bone1Matrix[1])), endEffector_position - root_top);
	glm::vec3 vec5 = glm::cross(glm::normalize(glm::vec3(bone2Matrix[1])), endEffector_position - bone1_end);
	glm::vec3 vec6 = glm::cross(glm::normalize(glm::vec3(bone3Matrix[1])), endEffector_position - bone2_end);
	glm::vec3 vec7 = glm::cross(glm::normalize(glm::vec3(bone1Matrix[0])), endEffector_position - root_top);
	glm::vec3 vec8 = glm::cross(glm::normalize(glm::vec3(bone2Matrix[0])), endEffector_position - bone1_end);
	glm::vec3 vec9 = glm::cross(glm::normalize(glm::vec3(bone3Matrix[0])), endEffector_position - bone2_end);

	jacobian_vectors =
	{
		vec1,
		vec2,
		vec3,
		vec4,
		vec5,
		vec6,
		vec7,
		vec8,
		vec9
	};
}

void Bone_Animation::reset()
{
	rotation_degree_vector =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f}
	};
}

