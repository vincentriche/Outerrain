#include "gpuHeightfield.h"
#include "mathUtils.h"

/*
\brief Constructor
*/
GPUHeightfield::GPUHeightfield() : Heightfield()
{
	InitGPUPrograms();
}

/*
\brief Constructor
\param nx width size of field
\param ny height size of field
\param bottomLeft bottom left vertex world coordinates
\param topRight top right vertex world coordinates
*/
GPUHeightfield::GPUHeightfield(int nx, int ny, const Box2D& bbox) : Heightfield(nx, ny, bbox)
{
	InitGPUPrograms();
}

/*
\brief Constructor
\param nx width size of field
\param ny height size of field
\param bottomLeft bottom left vertex world coordinates
\param topRight top right vertex world coordinates
\param value default value for the field
*/
GPUHeightfield::GPUHeightfield(int nx, int ny, const Box2D& bbox, float value) : Heightfield(nx, ny, bbox, value)
{
	InitGPUPrograms();
}

/*
\brief Constructor from a file
\param file file path
\param nx width size of field
\param ny height size of field
\param bottomLeft bottom left vertex world coordinates
\param topRight top right vertex world coordinates
*/
GPUHeightfield::GPUHeightfield(const std::string& file, float minAlt, float maxAlt, int nx, int ny, const Box2D& bbox) : Heightfield(file, minAlt, maxAlt, nx, ny, bbox)
{
	InitGPUPrograms();
}

/*
\brief Constructor from a noise
\param nx width size of field
\param ny height size of field
\param bottomLeft bottom left vertex world coordinates
\param topRight top right vertex world coordinates
\param amplitude noise amplitude
\param freq noise frequency
\param oct noise octave count
\param type fractal type. See enum.
*/
GPUHeightfield::GPUHeightfield(int nx, int ny, const Box2D& bbox, const Noise& n, float amplitude, float freq, int oct, FractalType type) : Heightfield(nx, ny, bbox, n, amplitude, freq, oct, type)
{
	InitGPUPrograms();
}

/*
\brief Constructor from a noise
\param nx width size of field
\param ny height size of field
\param bottomLeft bottom left vertex world coordinates
\param topRight top right vertex world coordinates
\param amplitude noise amplitude
\param freq noise frequency
\param oct noise octave count
\param offset noise offset vector
\param type fractal type. See enum.
*/
GPUHeightfield::GPUHeightfield(int nx, int ny, const Box2D& bbox, const Noise& n, float amplitude, float freq, int oct, const Vector3& offset, FractalType type) : Heightfield(nx, ny, bbox, n, amplitude, freq, oct, offset, type)
{
	InitGPUPrograms();
}

/*
\brief Constructor from TerrainSettings class for convenience and consistancy.
\param settings TerrainSettings for the heightfield.
*/
GPUHeightfield::GPUHeightfield(const TerrainSettings& settings) : Heightfield(settings)
{
	InitGPUPrograms();
}

/*
\brief Destructor
*/
GPUHeightfield::~GPUHeightfield()
{
	glDeleteBuffers(1, &dataBuffer);
	computeShader.Release();
}

/*
\brief todo
*/
void GPUHeightfield::InitGPUPrograms()
{
	heightIntegerData.resize(values.size());
	computeShader = Shader("Shaders/HeightfieldCompute.glsl");
	computeShader.PrintCompileErrors();

	// Compute thread count
	GLuint computeShaderProgram = computeShader.GetProgram();
	GLint threads[3] = {};
	glGetProgramiv(computeShaderProgram, GL_COMPUTE_WORK_GROUP_SIZE, threads);
	threadGroupCount = values.size() / threads[0];
	if (values.size() % threads[0] > 0)
		threadGroupCount++;
}

/*
\brief todo
*/
void GPUHeightfield::GenerateBuffers()
{
	for (int i = 0; i < heightIntegerData.size(); i++)
		heightIntegerData[i] = (int)values[i];
	computeShader.Attach();
	glGenBuffers(1, &dataBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int) * heightIntegerData.size(), &heightIntegerData.front(), GL_STREAM_COPY);
}

/*
\brief todo
*/
void GPUHeightfield::ThermalWeathering(float amplitude, float tanThresholdAngle)
{
	// Prepare buffers
	GenerateBuffers();

	// Dispatch
	computeShader.Attach();
	glDispatchCompute(threadGroupCount, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	
	// Update CPU data
	glGetNamedBufferSubData(dataBuffer, 0, sizeof(int) * heightIntegerData.size(), heightIntegerData.data());
	for (int i = 0; i < values.size(); i++)
	{
		float newVal = (float)heightIntegerData[i];
		values[i] = newVal;
	}
	glDeleteBuffers(1, &dataBuffer);
}