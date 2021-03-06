/*
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 */

#include "Constants.h"

namespace octronic::dream
{
    // Misc =====================================================================
    const string Constants::DIR_PATH_SEP = "/";
    const string Constants::DIR_PATH_SEP_WINDOWS = "\\";
    const string Constants::PATH_DELIMETER = "::";

    // Project ==================================================================
    const string Constants::PROJECT_DEFAULT_NAME = "Untitled Project";
    const string Constants::PROJECT_DIRECTORY_ARG = "--project-dir";
    const string Constants::PROJECT_UUID_ARG = "--uuid";
    const string Constants::PROJECT_EXTENSION = ".json";
    const string Constants::PROJECT_PATH_SEP = "/";
    const string Constants::PROJECT_UUID = "uuid";
    const string Constants::PROJECT_NAME = "name";
    const string Constants::PROJECT_SCENE_ARRAY = "scenes";
    const string Constants::PROJECT_ASSET_ARRAY = "assets";
    const string Constants::PROJECT_STARTUP_SCENE = "startupScene";

    // Asset ====================================================================
    const string Constants::UUID = "uuid";
    const string Constants::NAME = "name";

    // Types
    const string Constants::ASSET_TYPE = "type";
    const string Constants::ASSET_TYPE_ANIMATION = "animation";
    const string Constants::ASSET_TYPE_PATH = "path";
    const string Constants::ASSET_TYPE_AUDIO = "audio";
    const string Constants::ASSET_TYPE_FONT = "font";
    const string Constants::ASSET_TYPE_MODEL = "model";
    const string Constants::ASSET_TYPE_PHYSICS_OBJECT = "physicsObject";
    const string Constants::ASSET_TYPE_SCRIPT = "script";
    const string Constants::ASSET_TYPE_SHADER = "shader";
    const string Constants::ASSET_TYPE_TEXTURE = "texture";
    const string Constants::ASSET_TYPE_MATERIAL = "material";

    // Formats
    const string Constants::ASSET_FORMAT = "format";
    const string Constants::ASSET_FORMAT_SCRIPT_LUA = "lua";
    const string Constants::ASSET_FORMAT_MODEL_ASSIMP = "assimp";
    const string Constants::ASSET_FORMAT_AUDIO_WAV = "wav";
    const string Constants::ASSET_FORMAT_AUDIO_OGG = "ogg";
    const string Constants::ASSET_FORMAT_DREAM = "dream";
    const string Constants::ASSET_FORMAT_FONT_TTF = "ttf";
    const string Constants::ASSET_FORMAT_SHADER_GLSL = "glsl";
    const string Constants::ASSET_FORMAT_SHADER_GLES = "gles";

    const string Constants::ASSET_TYPE_ANIMATION_READABLE = "Animation";
    const string Constants::ASSET_TYPE_PATH_READABLE = "Path";
    const string Constants::ASSET_TYPE_AUDIO_READABLE = "Audio";
    const string Constants::ASSET_TYPE_FONT_READABLE = "Font";
    const string Constants::ASSET_TYPE_MODEL_READABLE = "Model";
    const string Constants::ASSET_TYPE_PHYSICS_OBJECT_READABLE = "Physics Object";
    const string Constants::ASSET_TYPE_SCRIPT_READABLE = "Script";
    const string Constants::ASSET_TYPE_SHADER_READABLE = "Shader";
    const string Constants::ASSET_DEFINITION_DEFAULT_NAME = "New Asset Definition";
    const string Constants::ASSET_TYPE_TEXTURE_READABLE = "Texture";
    const string Constants::ASSET_TYPE_MATERIAL_READABLE = "Material";
    const string Constants::ASSET_ATTR_GROUP = "group";
    const string Constants::ASSET_ATTR_GROUP_DEFAULT = "None";

    const string Constants::ASSET_FORMAT_SCRIPT_LUA_READABLE = "Lua";
    const string Constants::ASSET_FORMAT_MODEL_ASSIMP_READABLE = "Assimp Model";
    const string Constants::ASSET_FORMAT_AUDIO_OGG_READABLE = "Ogg";
    const string Constants::ASSET_FORMAT_AUDIO_WAV_READABLE = "Wav";
    const string Constants::ASSET_FORMAT_DREAM_READABLE = "Dream";
    const string Constants::ASSET_FORMAT_FONT_TTF_READABLE = "TTF Font";
    const string Constants::ASSET_FORMAT_SHADER_GLSL_READABLE = "GLSL";

    // Scene ====================================================================
    const string Constants::SCENE_ROOT_ENTITY = "root";
    const string Constants::SCENE_CLEAR_COLOR = "clearColor";
    const string Constants::SCENE_GRAVITY = "gravity";
    const string Constants::SCENE_DEFAULT_NAME = "Untitled Scene";
    const string Constants::SCENE_CAMERA = "camera";
    const string Constants::SCENE_SHADOW_PASS_SHADER = "shadow_pass_shader";
    const string Constants::SCENE_FONT_SHADER = "font_shader";
    const string Constants::SCENE_SPRITE_SHADER = "sprite_shader";
    const string Constants::SCENE_INPUT_SCRIPT = "input_script";
    const string Constants::SCENE_ENVIRONMENT_TEXTURE = "environment_texture";
    const string Constants::SCENE_ENVIRONMENT_SHADER = "environment_shader";

    // Camera ==================================================================
    const string Constants::CAMERA_FOV = "fov";
    const string Constants::CAMERA_MESH_CULL_DISTANCE = "mesh_cull_distance";
    const string Constants::CAMERA_MIN_DRAW_DISTANCE = "min_draw";
    const string Constants::CAMERA_MAX_DRAW_DISTANCE = "max_draw";
    const string Constants::CAMERA_FREE_TRANSFORM = "free_transform";
    const string Constants::CAMERA_ENTITY_UUID = "entity_uuid";
    const string Constants::CAMERA_USE_ENTITY = "use_entity";


    // Entity ==================================================================
    const string Constants::ENTITY = "entity";
    const string Constants::ENTITY_ROOT_NAME = "Root Entity";
    const string Constants::ENTITY_DEFAULT_NAME = "New Entity";
    const string Constants::ENTITY_CHILDREN = "children";
    const string Constants::ENTITY_ASSET_INSTANCES = "assetInstances";
    const string Constants::ENTITY_TEMPLATE = "template";
    const string Constants::ENTITY_FONT_COLOR = "font_color";
    const string Constants::ENTITY_FONT_SCALE = "font_scale";
    const string Constants::ENTITY_FONT_TEXT = "font_text";

    // Transform ================================================================
    const string Constants::TRANSFORM = "transform";
    const string Constants::TRANSLATION = "translation";
    const string Constants::YAW = "yaw";
    const string Constants::PITCH = "pitch";
    const string Constants::ROLL = "roll";
    const string Constants::SCALE = "scale";

    // Generic ==================================================================
    const string Constants::W = "w";
    const string Constants::X = "x";
    const string Constants::Y = "y";
    const string Constants::Z = "z";

    // Font ================================================================
	const string Constants::ASSET_ATTR_FONT_SHADER_ID = "shader_id";
	const string Constants::ASSET_ATTR_FONT_SIZE = "size";

    // Font ================================================================
	const string Constants::ASSET_ATTR_SPRITE_WIDTH = "width";
	const string Constants::ASSET_ATTR_SPRITE_HEIGHT = "height";
	const string Constants::ASSET_ATTR_SPRITE_TEXTURE = "texture";

    // Path ================================================================
    const string Constants::ASSET_ATTR_ID            = "id";
    const string Constants::ASSET_ATTR_VELOCITY      = "velocity";
    const string Constants::ASSET_ATTR_POSITION      = "position";
    const string Constants::ASSET_ATTR_KEYFRAMES     = "keyframes";
    const string Constants::ASSET_ATTR_START_TIME    = "startTime";
    const string Constants::ASSET_ATTR_WRAP          = "wrap";
    const string Constants::ASSET_ATTR_LOOP          = "loop";
    const string Constants::ASSET_ATTR_INTERPOLATION = "interpolation";
    const string Constants::ASSET_ATTR_CONTROL_POINTS = "ctrl_points";
    const string Constants::ASSET_ATTR_INDEX = "index";
    const string Constants::ASSET_ATTR_STEP_SCALAR = "scalar";
    const int Constants::DREAM_PATH_STOPPED = 0;
    const int Constants::DREAM_PATH_PLAYING = 1;
    const int Constants::DREAM_PATH_PAUSED  = 2;
    const int Constants::MAX_FRAME_ADVANCE       = 10;
    const string Constants::DREAM_PATH_SPLINE_TYPE  = "spline_type";
    const string Constants::DREAM_PATH_TYPE_OPEN = "open";
    const string Constants::DREAM_PATH_TYPE_CLAMPED = "clamped";
    const string Constants::DREAM_PATH_TYPE_BEZIER = "bezier";

    // Physics ==================================================================
    const string Constants::ASSET_ATTR_MASS   = "mass";
    const string Constants::ASSET_ATTR_MARGIN = "margin";
    const string Constants::ASSET_ATTR_RADIUS = "radius";
    const string Constants::ASSET_ATTR_HEIGHT = "height";
    const string Constants::ASSET_ATTR_NORMAL = "normal";
    const string Constants::ASSET_ATTR_CONSTANT = "constant";
    const string Constants::ASSET_ATTR_SIZE = "size";
    const string Constants::ASSET_ATTR_COMPOUND_CHILDREN = "compoundChildren";
    const string Constants::ASSET_ATTR_COLLISION_MODEL = "collisionModel";
    const string Constants::ASSET_ATTR_KINEMATIC = "kinematic";
    const string Constants::ASSET_ATTR_CONTROLLABLE = "controllable";
    const string Constants::ASSET_ATTR_CCD_SPR = "ccd_spr";
    const string Constants::ASSET_ATTR_RESTITUTION = "restitution";
    const string Constants::ASSET_ATTR_FRICTION = "friction";
    const string Constants::ASSET_ATTR_ANGULAR_FENTITY = "angular_factor";
    const string Constants::ASSET_ATTR_LINEAR_FENTITY = "linear_factor";
    const string Constants::ASSET_ATTR_ANGULAR_VELOCITY = "angular_velocity";
    const string Constants::ASSET_ATTR_LINEAR_VELOCITY = "linear_velocity";


    const string Constants::COLLISION_SHAPE_SPHERE = "btShpereShape";
    const string Constants::COLLISION_SHAPE_BOX = "btBoxShape";
    const string Constants::COLLISION_SHAPE_CYLINDER = "btCylinderShape";
    const string Constants::COLLISION_SHAPE_CAPSULE = "btCapsuleShape";
    const string Constants::COLLISION_SHAPE_CONE = "btConeShape";
    const string Constants::COLLISION_SHAPE_MULTI_SPHERE = "btMultiSphereShape";
    const string Constants::COLLISION_SHAPE_CONVEX_HULL = "btConvexHullShape";
    const string Constants::COLLISION_SHAPE_CONVEX_TRIANGLE_MESH = "btConvexTriangleMeshShape";
    const string Constants::COLLISION_SHAPE_BVH_TRIANGLE_MESH = "btBvhTriangleMeshShape";
    const string Constants::COLLISION_SHAPE_HEIGHTFIELD_TERRAIN = "btHeightfieldTerrainShape";
    const string Constants::COLLISION_SHAPE_STATIC_PLANE = "btStaticPlaneShape";
    const string Constants::COLLISION_SHAPE_COMPOUND = "btCompoundShape";

    const string Constants::COLLISION_SHAPE_SPHERE_READABLE = "Sphere";
    const string Constants::COLLISION_SHAPE_BOX_READABLE = "Box";
    const string Constants::COLLISION_SHAPE_CYLINDER_READABLE = "Cylinder";
    const string Constants::COLLISION_SHAPE_CAPSULE_READABLE = "Capsule";
    const string Constants::COLLISION_SHAPE_CONE_READABLE = "Cone";
    const string Constants::COLLISION_SHAPE_MULTI_SPHERE_READABLE = "Multi-Sphere";
    const string Constants::COLLISION_SHAPE_CONVEX_HULL_READABLE = "Convex Hull";
    const string Constants::COLLISION_SHAPE_CONVEX_TRIANGLE_MESH_READABLE = "Convex Triangle Mesh";
    const string Constants::COLLISION_SHAPE_BVH_TRIANGLE_MESH_READABLE = "BVH Triangle Mesh";
    const string Constants::COLLISION_SHAPE_HEIGHTFIELD_TERRAIN_READABLE = "Heightfield Terrain";
    const string Constants::COLLISION_SHAPE_STATIC_PLANE_READABLE = "Static Plane";
    const string Constants::COLLISION_SHAPE_COMPOUND_READABLE = "Compound Shape";

    // Event ====================================================================
    const string Constants::EVENT_SENDER = "sender";
    const string Constants::EVENT_TYPE = "type";
    const string Constants::EVENT_TYPE_COLLISION = "collision";

    // Material
    const string Constants::ASSET_ATTR_MATERIAL_SHADER = "shader";
    const string Constants::ASSET_ATTR_MATERIAL_ALBEDO = "albedo";
    const string Constants::ASSET_ATTR_MATERIAL_NORMAL = "normal";
    const string Constants::ASSET_ATTR_MATERIAL_METALLIC = "metallic";
    const string Constants::ASSET_ATTR_MATERIAL_ROUGHNESS = "roughness";
    const string Constants::ASSET_ATTR_MATERIAL_AO = "ao";

    // Model ===================================================================
    const string Constants::ASSET_ATTR_MODEL_MATERIAL_LIST = "material_list";
    const string Constants::ASSET_ATTR_MODEL_MODEL_MATERIAL = "model_material";
    const string Constants::ASSET_ATTR_MODEL_DREAM_MATERIAL = "dream_material";

    // Lua =====================================================================
    const string Constants::SCRIPT_INIT_FUNCTION   = "onInit";
    const string Constants::SCRIPT_UPDATE_FUNCTION = "onUpdate";
    const string Constants::SCRIPT_INPUT_FUNCTION  = "onInput";
    const string Constants::SCRIPT_EVENT_FUNCTION  = "onEvent";
    const string Constants::SCRIPT_DESTROY_FUNCTION  = "onDestroy";

    // Shader ==================================================================
    const string Constants::SHADER_FRAGMENT = ".frag";
    const string Constants::SHADER_VERTEX   = ".vert";

    const string Constants::SHADER_GLSL_FRAGMENT_FILE_NAME
        = Constants::ASSET_FORMAT_SHADER_GLSL + Constants::SHADER_FRAGMENT ;

    const string Constants::SHADER_GLSL_VERTEX_FILE_NAME
        = Constants::ASSET_FORMAT_SHADER_GLSL +Constants::SHADER_VERTEX;


    const string Constants::SHADER_GLES_FRAGMENT_FILE_NAME
        = Constants::ASSET_FORMAT_SHADER_GLES + Constants::SHADER_FRAGMENT ;

    const string Constants::SHADER_GLES_VERTEX_FILE_NAME
        = Constants::ASSET_FORMAT_SHADER_GLES +Constants::SHADER_VERTEX;

    // Texture =================================================================
    const string Constants::ASSET_ATTR_TEXTURE_IS_ENVIRONMENT = "is_environment";
    const string Constants::ASSET_ATTR_TEXTURE_EQUI_TO_CUBEMAP_SHADER = "equi_to_cubemap_shader";
    const string Constants::ASSET_ATTR_TEXTURE_IRRADIANCE_MAP_SHADER = "irradiance_map_shader";
    const string Constants::ASSET_ATTR_TEXTURE_PREFILTER_SHADER = "prefilter_shader";
    const string Constants::ASSET_ATTR_TEXTURE_BRDF_LUT_SHADER = "brdf_lut_shader";
    const string Constants::ASSET_ATTR_TEXTURE_FLIP_VERTICAL = "flip_vertical";


    // Audio ===================================================================
    const string Constants::ASSET_ATTR_SPECTRUM_ANALYSER = "spectrum_analyser";
    const string Constants::ASSET_ATTR_AUDIO_EVENT_MARKERS = "event_markers";
    const string Constants::ASSET_ATTR_AUDIO_EM_INDEX = "index";
    const string Constants::ASSET_ATTR_AUDIO_EM_S_INDEX = "sample_index";
    const string Constants::ASSET_ATTR_AUDIO_EM_NAME = "name";
    const string Constants::ASSET_ATTR_AUDIO_EM_REPEAT = "repeat";
    const string Constants::ASSET_ATTR_AUDIO_EM_REPEAT_PERIOD = "repeat_period";

    // Animation / Keyframe ====================================================
    const string Constants::KEYFRAME_ID = "kf_id";
    const string Constants::KEYFRAME_TRANSFORM = "transform";
    const string Constants::KEYFRAME_TIME = "time";
    const string Constants::KEYFRAME_DURATION = "duration";
    const string Constants::KEYFRAME_LOOPING = "looping";
    const string Constants::KEYFRAME_EASING_TYPE = "easing_type";
    const string Constants::ANIMATION_RELATIVE = "relative";

    // Data ====================================================================

    map<AssetType,string> Constants::DREAM_ASSET_TYPES_MAP =
    {
        {ASSET_TYPE_ENUM_ANIMATION,        ASSET_TYPE_ANIMATION},
        {ASSET_TYPE_ENUM_AUDIO,            ASSET_TYPE_AUDIO},
        {ASSET_TYPE_ENUM_FONT,             ASSET_TYPE_FONT},
        {ASSET_TYPE_ENUM_MATERIAL,         ASSET_TYPE_MATERIAL},
        {ASSET_TYPE_ENUM_MODEL,            ASSET_TYPE_MODEL},
        {ASSET_TYPE_ENUM_PATH,             ASSET_TYPE_PATH},
        {ASSET_TYPE_ENUM_PHYSICS_OBJECT,   ASSET_TYPE_PHYSICS_OBJECT},
        {ASSET_TYPE_ENUM_SCRIPT,           ASSET_TYPE_SCRIPT},
        {ASSET_TYPE_ENUM_SHADER,           ASSET_TYPE_SHADER},
        {ASSET_TYPE_ENUM_TEXTURE,          ASSET_TYPE_TEXTURE}
    };

    vector<string> Constants::DREAM_ASSET_TYPES_READABLE_VECTOR =
    {
        ASSET_TYPE_ANIMATION_READABLE,
        ASSET_TYPE_AUDIO_READABLE,
        ASSET_TYPE_FONT_READABLE,
        ASSET_TYPE_MATERIAL_READABLE,
        ASSET_TYPE_MODEL_READABLE,
        ASSET_TYPE_PATH_READABLE,
        ASSET_TYPE_PHYSICS_OBJECT_READABLE,
        ASSET_TYPE_SCRIPT_READABLE,
        ASSET_TYPE_SHADER_READABLE,
        ASSET_TYPE_TEXTURE_READABLE
    };

    map<AssetType,vector<string>> Constants::DREAM_ASSET_FORMATS_MAP =
    {
        {ASSET_TYPE_ENUM_ANIMATION,{ASSET_FORMAT_DREAM}},
        {ASSET_TYPE_ENUM_AUDIO,{ASSET_FORMAT_AUDIO_WAV,ASSET_FORMAT_AUDIO_OGG}},
        {ASSET_TYPE_ENUM_FONT,{ASSET_FORMAT_FONT_TTF}},
        {ASSET_TYPE_ENUM_MATERIAL,{ASSET_FORMAT_DREAM}},
        {ASSET_TYPE_ENUM_MODEL,{ASSET_FORMAT_MODEL_ASSIMP}},
        {ASSET_TYPE_ENUM_PATH,{ASSET_FORMAT_DREAM}},
        {ASSET_TYPE_ENUM_PHYSICS_OBJECT,{
			COLLISION_SHAPE_SPHERE, COLLISION_SHAPE_BOX, COLLISION_SHAPE_CYLINDER,
			COLLISION_SHAPE_CAPSULE, COLLISION_SHAPE_CONE,COLLISION_SHAPE_MULTI_SPHERE,
			COLLISION_SHAPE_CONVEX_HULL, COLLISION_SHAPE_CONVEX_TRIANGLE_MESH,
			COLLISION_SHAPE_BVH_TRIANGLE_MESH, COLLISION_SHAPE_HEIGHTFIELD_TERRAIN,
			COLLISION_SHAPE_STATIC_PLANE, COLLISION_SHAPE_COMPOUND
		}},
        {ASSET_TYPE_ENUM_SCRIPT,{ASSET_FORMAT_SCRIPT_LUA}},
        {ASSET_TYPE_ENUM_SHADER,{ASSET_FORMAT_SHADER_GLSL}},
        {ASSET_TYPE_ENUM_TEXTURE,{ASSET_FORMAT_DREAM}}
    };

    string
    Constants::getAssetTypeStringFromTypeEnum
    (AssetType type)
    {
        switch (type)
        {
            case ASSET_TYPE_ENUM_ANIMATION:      return ASSET_TYPE_ANIMATION;
            case ASSET_TYPE_ENUM_PATH:           return ASSET_TYPE_PATH;
            case ASSET_TYPE_ENUM_AUDIO:          return ASSET_TYPE_AUDIO;
            case ASSET_TYPE_ENUM_FONT:           return ASSET_TYPE_FONT;
            case ASSET_TYPE_ENUM_MATERIAL:       return ASSET_TYPE_MATERIAL;
            case ASSET_TYPE_ENUM_MODEL:          return ASSET_TYPE_MODEL;
            case ASSET_TYPE_ENUM_PHYSICS_OBJECT: return ASSET_TYPE_PHYSICS_OBJECT;
            case ASSET_TYPE_ENUM_SCRIPT:         return ASSET_TYPE_SCRIPT;
            case ASSET_TYPE_ENUM_SHADER:         return ASSET_TYPE_SHADER;
            case ASSET_TYPE_ENUM_TEXTURE:        return ASSET_TYPE_TEXTURE;
            case ASSET_TYPE_ENUM_NONE:
                return "";
        }
        return "";
    }

    AssetType
    Constants::getAssetTypeEnumFromString
    (const string& type)
    {
        AssetType retval = ASSET_TYPE_ENUM_NONE;
        if (type == ASSET_TYPE_ANIMATION || type == ASSET_TYPE_ANIMATION_READABLE) retval =  ASSET_TYPE_ENUM_ANIMATION;
        else if (type == ASSET_TYPE_AUDIO || type == ASSET_TYPE_AUDIO_READABLE) retval = ASSET_TYPE_ENUM_AUDIO;
        else if (type == ASSET_TYPE_FONT || type == ASSET_TYPE_FONT_READABLE) retval = ASSET_TYPE_ENUM_FONT;
        else if (type == ASSET_TYPE_MATERIAL || type == ASSET_TYPE_MATERIAL_READABLE) retval = ASSET_TYPE_ENUM_MATERIAL;
        else if (type == ASSET_TYPE_MODEL || type == ASSET_TYPE_MODEL_READABLE) retval = ASSET_TYPE_ENUM_MODEL;
        else if (type == ASSET_TYPE_PATH || type == ASSET_TYPE_PATH_READABLE) retval = ASSET_TYPE_ENUM_PATH;
        else if (type == ASSET_TYPE_PHYSICS_OBJECT || type == ASSET_TYPE_PHYSICS_OBJECT_READABLE) retval = ASSET_TYPE_ENUM_PHYSICS_OBJECT;
        else if (type == ASSET_TYPE_SCRIPT || type == ASSET_TYPE_SCRIPT_READABLE) retval = ASSET_TYPE_ENUM_SCRIPT;
        else if (type == ASSET_TYPE_SHADER || type == ASSET_TYPE_SHADER_READABLE) retval = ASSET_TYPE_ENUM_SHADER;
        else if (type == ASSET_TYPE_TEXTURE || type == ASSET_TYPE_TEXTURE_READABLE) retval =  ASSET_TYPE_ENUM_TEXTURE;
        return retval;
    }

    string
    Constants::getAssetTypeReadableNameFromString
    (const string& type)
    {
        if (type == ASSET_TYPE_ANIMATION) return ASSET_TYPE_ANIMATION_READABLE;
        else if (type == ASSET_TYPE_AUDIO) return ASSET_TYPE_AUDIO_READABLE;
        else if (type == ASSET_TYPE_FONT) return ASSET_TYPE_FONT_READABLE;
        else if (type == ASSET_TYPE_MATERIAL) return ASSET_TYPE_MATERIAL_READABLE;
        else if (type == ASSET_TYPE_MODEL) return ASSET_TYPE_MODEL_READABLE;
        else if (type == ASSET_TYPE_PATH) return ASSET_TYPE_PATH_READABLE;
        else if (type == ASSET_TYPE_PHYSICS_OBJECT) return ASSET_TYPE_PHYSICS_OBJECT_READABLE;
        else if (type == ASSET_TYPE_SCRIPT) return ASSET_TYPE_SCRIPT_READABLE;
        else if (type == ASSET_TYPE_SHADER) return ASSET_TYPE_SHADER_READABLE;
        else if (type == ASSET_TYPE_TEXTURE) return ASSET_TYPE_TEXTURE_READABLE;
        return "";
    }

    string
    Constants::getAssetFormatReadableNameFromString
    (const string& format)
    {
        // Script
        if (format == ASSET_FORMAT_SCRIPT_LUA) return ASSET_FORMAT_SCRIPT_LUA_READABLE;
        // Model
        else if (format == ASSET_FORMAT_MODEL_ASSIMP) return ASSET_FORMAT_MODEL_ASSIMP_READABLE;
        // Audio
        else if (format == ASSET_FORMAT_AUDIO_OGG) return ASSET_FORMAT_AUDIO_OGG_READABLE;
        else if (format == ASSET_FORMAT_AUDIO_WAV) return ASSET_FORMAT_AUDIO_WAV_READABLE;
        // Font
        else if (format == ASSET_FORMAT_FONT_TTF) return ASSET_FORMAT_FONT_TTF_READABLE;
        // Shader
        else if (format == ASSET_FORMAT_SHADER_GLSL) return ASSET_FORMAT_SHADER_GLSL_READABLE;
        // Dream
        else if (format == ASSET_FORMAT_DREAM) return ASSET_FORMAT_DREAM_READABLE;
        // Physics
        else if (format == COLLISION_SHAPE_SPHERE) return COLLISION_SHAPE_SPHERE_READABLE;
        else if (format == COLLISION_SHAPE_BOX) return COLLISION_SHAPE_BOX_READABLE;
        else if (format == COLLISION_SHAPE_CYLINDER) return COLLISION_SHAPE_CYLINDER_READABLE;
        else if (format == COLLISION_SHAPE_CAPSULE) return COLLISION_SHAPE_CAPSULE_READABLE;
        else if (format == COLLISION_SHAPE_CONE) return COLLISION_SHAPE_MULTI_SPHERE_READABLE;
        else if (format == COLLISION_SHAPE_CONVEX_HULL) return COLLISION_SHAPE_CONVEX_HULL_READABLE;
        else if (format == COLLISION_SHAPE_CONVEX_TRIANGLE_MESH) return COLLISION_SHAPE_CONVEX_TRIANGLE_MESH_READABLE;
        else if (format == COLLISION_SHAPE_BVH_TRIANGLE_MESH) return COLLISION_SHAPE_BVH_TRIANGLE_MESH_READABLE;
        else if (format == COLLISION_SHAPE_HEIGHTFIELD_TERRAIN) return COLLISION_SHAPE_HEIGHTFIELD_TERRAIN_READABLE;
        else if (format == COLLISION_SHAPE_STATIC_PLANE) return COLLISION_SHAPE_STATIC_PLANE_READABLE;
        else if (format == COLLISION_SHAPE_COMPOUND) return COLLISION_SHAPE_COMPOUND_READABLE;
        else if (format == COLLISION_SHAPE_MULTI_SPHERE) return COLLISION_SHAPE_MULTI_SPHERE_READABLE;

        return "";
    }

    string
    Constants::getAssetFormatStringFromReadableName
    (const string& format)
    {
        if      (format == ASSET_FORMAT_SCRIPT_LUA_READABLE) return ASSET_FORMAT_SCRIPT_LUA;
        else if (format == ASSET_FORMAT_MODEL_ASSIMP_READABLE) return ASSET_FORMAT_MODEL_ASSIMP;
        else if (format == ASSET_FORMAT_AUDIO_OGG_READABLE) return ASSET_FORMAT_AUDIO_OGG;
        else if (format == ASSET_FORMAT_AUDIO_WAV_READABLE) return ASSET_FORMAT_AUDIO_WAV;
        else if (format == ASSET_FORMAT_FONT_TTF_READABLE) return ASSET_FORMAT_FONT_TTF;
        else if (format == ASSET_FORMAT_SHADER_GLSL_READABLE) return ASSET_FORMAT_SHADER_GLSL;
        else if (format == ASSET_FORMAT_DREAM_READABLE) return ASSET_FORMAT_DREAM;
        else if (format == COLLISION_SHAPE_SPHERE_READABLE) return COLLISION_SHAPE_SPHERE;
        else if (format == COLLISION_SHAPE_BOX_READABLE) return COLLISION_SHAPE_BOX;
        else if (format == COLLISION_SHAPE_CYLINDER_READABLE) return COLLISION_SHAPE_CYLINDER;
        else if (format == COLLISION_SHAPE_CAPSULE_READABLE) return COLLISION_SHAPE_CAPSULE;
        else if (format == COLLISION_SHAPE_CONE_READABLE) return COLLISION_SHAPE_CONE;
        else if (format == COLLISION_SHAPE_CONVEX_HULL_READABLE) return COLLISION_SHAPE_CONVEX_HULL;
        else if (format == COLLISION_SHAPE_CONVEX_TRIANGLE_MESH_READABLE) return COLLISION_SHAPE_CONVEX_TRIANGLE_MESH;
        else if (format == COLLISION_SHAPE_BVH_TRIANGLE_MESH_READABLE) return COLLISION_SHAPE_BVH_TRIANGLE_MESH;
        else if (format == COLLISION_SHAPE_HEIGHTFIELD_TERRAIN_READABLE) return COLLISION_SHAPE_HEIGHTFIELD_TERRAIN;
        else if (format == COLLISION_SHAPE_STATIC_PLANE_READABLE) return COLLISION_SHAPE_STATIC_PLANE;
        else if (format == COLLISION_SHAPE_COMPOUND_READABLE) return COLLISION_SHAPE_COMPOUND;
        else if (format == COLLISION_SHAPE_MULTI_SPHERE_READABLE) return COLLISION_SHAPE_MULTI_SPHERE;
        return "";
    }

    vector<string> Constants::DREAM_PATH_SPLINE_TYPES
    { DREAM_PATH_TYPE_OPEN, DREAM_PATH_TYPE_BEZIER, DREAM_PATH_TYPE_CLAMPED };
}


