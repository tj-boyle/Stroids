/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __INSTANCECLASS_H_
#define __INSTANCECLASS_H_

#include "ME\Mesh\ModelClass.h"

namespace MyEngine
{

class MyEngineDLL InstanceClass
{
	bool m_bInstanciated;	//Done instanciated flag
	bool m_bVisible;		//visibility flag
	bool m_bVisibleAxis;	//Visible Axis flag
	bool m_bVisibleFrameBO;	//Visible Frame Bounding Object flag
	bool m_bVisibleGrandBO;	//Visible Grand Bounding Object flag
	bool m_bCollidable;		//Collisionable flag
	
	int m_nGroups;			//Number of groups
	int m_nStateLast;		//Last state visited
	int m_nStateCurrent;	//Current state
	int m_nStateNext;		//Next state to visit
	int m_nHP;				//Hit Points of the Instance
	int m_nCurrentFrame;	//Current frame to be rendered

	float m_fLastFrameDrawn; //Last frame rendered

	BoundingObjectClass* m_pGrandBO;	//Bounding Object that contains all frame Bounding Objects
	BoundingObjectClass* m_pFrameBO;	//Bounding Object of the current frame
	SystemSingleton* m_pSystem;				//System pointer
	ModelClass* m_pModel;				//Model from which this instance was instanciated
	AxisClass* m_pAxis;					//Axis of the instance
	GroupClass* m_pGroup;	//List of group pointers of the instance

	DWORD m_dLastRenderCall;	//Last render call

	String m_sName;				//Name of the instance

	matrix4 m_m4ToWorld;		//Model to world matrix

public:
	/* Constructor */
	InstanceClass(void);
	/* Copy Constructor */
	InstanceClass(const InstanceClass& other);
	/* Copy Assignment Operator */
	InstanceClass& operator=(const InstanceClass& other);
	/* Destructor */
	~InstanceClass(void);

	//Accessors
	/* Sets the Shader program */
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = MEDEFAULT);
	/* Sets the shader program to a program already compiled */
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = MEDEFAULT);

	/* Sets the Model to World matrix of the instance*/
	void SetModelMatrix(const matrix4 a_m4ToWorld = matrix4(1.0f));
	/* Gets the model to World matrix from the instance*/
	matrix4& GetModelMatrix(void);
	/* Property SetModelMatrix/GetModelMatrix*/
	__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) matrix4 ModelMatrix;

	/* Set the name of the instance */
	void SetName(String a_sName);
	/* Gets the name of the specified group*/
	String GetName(int nGroup = -1);

	/* Sets the Hit Points of the instance*/
	void SetHP(int a_nHP);
	/* Gets the Hit Points of the instance*/
	int GetHP(void);

	/* Sets the instance to be collidable */
	void SetCollidable(bool a_bCollidable);
	/* Asks the instance if its collidable*/
	bool GetCollidable(void);

	/* Sets the visibility flag */
	void SetVisible(bool a_bVisible);
	/* Gets the visibility flag */
	bool GetVisible(void);

	/* Set the visibility frag for the Frame Bounding object of the instance and the groups per name*/
	void SetVisibleFrameBO(bool a_bVisibleBO, String sIncludeGroup = "ALL");
	/* Set the visibility frag for the Frame Bounding object of the instance and the groups per index*/
	void SetVisibleFrameBO(bool a_bVisibleBO, int a_nIncludeGroup = -1); //a_nIncludeGroup = -1 for all -2 for none

	/* Set the visibility frag for the Grand Bounding object of the instance */
	void SetVisibleGrandBO(bool a_bVisibleBO);

	/* Set the visibility frag for the Axis of the instance and the groups*/
	void SetVisibleAxis(bool a_bVisibleAxis, bool a_bGroups = false);

	/*
		Gets the current state of the instance
	*/
	int GetCurrentState(void);

	/* Sets the next state of the instance */
	void SetNextState(int a_nNext, bool b_Force = false);
	/* Sets the current state of the instance (it forces the switch) */
	void SetCurrentSate(int a_nState);

	/* Change the shader program of a group finding it by name */
	void SetGroupShaderByName(String a_sProgramName = "Original", String a_sGroupName = "ALL", vector3 a_v3Tint = MEDEFAULT);
	/* Change the shader program of a group finding it by index */
	void SetGroupShaderByNumber(String a_sProgramName = "Original", int nGroup = -1, vector3 a_v3Tint = MEDEFAULT);
	/* Change the material of a group finding it by name, the material needs to be already compiled */
	void SetGroupMaterial(String a_sMaterialName, String a_sGroupName = "ALL");

	/* Asks the instance what is the last drawn frame */
	int GetLastFrameDrawn(void);

	/* Asks the instance what is its the number of groups*/
	int GetNumberOfGroups(void);

	/* Asks the instance what is its number of frames */
	int GetNumberOfFrames(void);

	/* Asks the instance for the vertices of the whole model */
	std::vector<vector3> GetVertices(void);

	/* Asks the instance for the Model for which it was instanciated from */
	ModelClass* GetModelInstanced(void);

	/* Asks the instance for its Grand Bounding Object*/
	BoundingObjectClass* GetGrandBoundingObject (void);

	/* Asks the instance for its Frame Bounding Object*/
	BoundingObjectClass* GetFrameBoundingObject (void);

	/* Asks the instance for the collision list of the groups colliding with the incoming instance's groups */
	std::vector<vector2> GetCollisionList(InstanceClass* a_pInstance);

	/* Sets the list of octants this instance is located on*/
	void SetOctantList(std::vector<int> a_lList);
	
	/* Creates an Instance of a previously loaded model */
	void InstanceModel(ModelClass& a_Model);

	/* Updates all the internal structures of the instance*/
	void Update(void);

	/* Adds all groups of the instance to the render list */
	void AddToRenderList(void);

	/* Asks the instance if its already done instanciated */
	bool IsInstanced(void);

	/* Identifies a group by name, the return will be -1 if the name is not found */
	int IdentifyGroup( String a_sName);

	/* Swap the materials of the instance */
	void SwapMaterials( String a_sOldMaterialName, String a_sNewMaterialName);

	/* Asks the instance if its colliding with another instance */
	bool IsColliding(InstanceClass* a_pInstance);

	/* Asks the instance if its colliding with a ray */
	int IsColliding(vector3 a_v3RayStart, vector3 a_vRayDirection);

	/* We need to disconect all the pointers that are shared amond the instances and the model */
	void DisconectPointers(void);

private:
	/* Gets a group by name */
	GroupClass* GetGroup(String a_sName);

	/* Initializes the variables */
	void Init(void);

	/* Release the fields in the class */
	void Release(void);

	/* Swaps Content with other Instance class */
	void Swap(InstanceClass& other);

	/* Identifies a state by name */
	int IdentifyState(StateClass* a_pState);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<InstanceClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<InstanceClass*>;

}

#endif //_INSTANCECLASS_H
