#pragma once
#include"Patient.h";
class DiseaseData
{
public:
	string diseaseName;
	string description;

	DiseaseData()
	{
		diseaseName = "";
		description = "";
	}
	DiseaseData(string name, string desc)
	{
		diseaseName = name;
		description = desc;
	}
};