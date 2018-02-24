#include "mainwindow.h"


void MainWindow::InitBasicTerrain()
{
	int res = 128;
	PerlinNoise n;
	//hf = new Heightfield(std::string("Data/Heightmaps/island.png"), 0, 50, res, res, Vector2(-res, res), Vector2(res, -res));
	hf = new Heightfield(res, res, Vector2(-128, 128), Vector2(128, -128), n, 25.0, 0.005, 8, FractalType::Ridge);
	
	UpdateMeshRenderer();
	orbiter.LookAt(hfObject->GetComponent<MeshModel>()->GetBounds());
}

void MainWindow::StreamPowerErosionStep()
{
	if (hf == nullptr)
		return;
	hf->StreamPowerErosion(1, 2.0);
	UpdateMeshRenderer();
}

void MainWindow::ThermalErosionStep()
{
	if (hf == nullptr)
		return;
	hf->ThermalWeathering(1, 0.08f);
	UpdateMeshRenderer();
}

void MainWindow::UpdateMeshRenderer()
{
	if (hfObject != nullptr)
		delete hfObject;

	hfObject = new GameObject();
	hfObject->AddComponent(hf->GetMeshModel());
	hfObject->AddComponent(new MeshRenderer(hfObject->GetComponent<MeshModel>(), MaterialModel::DefaultDiffuse()));
}

void MainWindow::ClearScene() 
{
	if (hf != nullptr)
		delete hf;
	if (hfObject != nullptr)
		delete hfObject;
}
