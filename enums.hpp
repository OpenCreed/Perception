#pragma once

enum class SegmentType
{
	Logical_SG = 1,
	JT_B_Rep = 2,
	PMI_Data = 3,
	Meta_Data = 4,
	Shape = 6,
	Shape_LOD0 = 7,
	Shape_LOD1 = 8,
	Shape_LOD2 = 9,
	Shape_LOD3 = 10,
	Shape_LOD4 = 11,
	Shape_LOD5 = 12,
	Shape_LOD6 = 13,
	Shape_LOD7 = 14,
	Shape_LOD8 = 15,
	Shape_LOD9 = 16,
	XT_B_Rep = 17,
	Wireframe_Rep = 18,
	ULP = 20,
	LWPA = 24
};

enum class ObjectType
{
	//Identifier to signal End-Of-Elements
	SIGNAL_END_OF_ELEMENTS,

	//Segment Type 1 (Logical_SG)
	Base_Node_Element,
	Group_Node_Element,
	Instance_Node_Element,
	LOD_Node_Element,
	Meta_Data_Node_Element,
	NULL_Shape_Node_Element,
	Part_Node_Element,
	Partition_Node_Element,
	Range_LOD_Node_Element,
	Switch_Node_Element,
	Base_Shape_Node_Element,
	Point_Set_Shape_Node_Element,
	Polygon_Set_Shape_Node_Element,
	Polyline_Set_Shape_Node_Element,
	Primitive_Set_Shape_Node_Element,
	Tri_Strip_Set_Shape_Node_Element,
	Vertex_Shape_Node_Element,
	Base_Attribute_Data,
	Draw_Style_Attribute_Element,
	Fragment_Shader_Attribute_Element,
	Geometric_Transform_Attribute_Element,
	Draw_Style_Attribute_Element,
	Fragment_Shader_Attribute_Element,
	Geometric_Transform_Attribute_Element,
	Infinite_Light_Attribute_Element,
	Light_Set_Attribute_Element,
	Linestyle_Attribute_Element,
	Material_Attribute_Element,
	Point_Light_Attribute_Element,
	Pointstyle_Attribute_Element,
	Shader_Effects_Attribute_Element,
	Texture_Image_Attribute_Element,
	Vertex_Shader_Attribute_Element,
	Fragment_Shader_Attribute_Element,
	Texture_Coordinate_Generator_Attribute_Element,
	Mapping_Plane_Element,
	Mapping_Cylinder_Element,
	Mapping_Sphere_Element,
	Mapping_TriPlanar_Element,
	Base_Property_Atom_Element,
	Date_Property_Atom_Element,
	Integer_Property_Atom_Element,
	Floating_Point_Property_Atom_Element,
	Late_Loaded_Property_Atom_Element,
	JT_Object_Reference_Property_Atom_Element,
	String_Property_Atom_Element,

	//Segment Type 2 (JT_B_Rep)
	JT_B_Rep_Element,

	//Segment Type 4 (Meta_Data)
	PMI_Manager_Meta_Data_Element,
	Property_Proxy_Meta_Data_Element,

	//Segment Type 6-16 (Shape_LODx)
	Null_Shape_LOD_Element,
	Point_Set_Shape_LOD_Element,
	Polyline_Set_Shape_LOD_Element,
	Primitive_Set_Shape_Element,
	Tri_Strip_Set_Shape_LOD_Element,
	Vertex_Shape_LOD_Element,

	//Segment Type 17 (XT_B_Rep)
	XT_B_Rep_Element,

	//Segment Type 18 (Wireframe_Rep)
	Wireframe_Rep_Element,

	//Segment Type 20 (ULP)
	JT_ULP_Element,

	//Segment Type 24 (LWPA)
	JT_LWPA_Element,
};