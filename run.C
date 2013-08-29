void run()
{

//	gSystem->CompileMacro("code//compile.cpp");


	gSystem->Load("code/dataset_cpp.dll");
	gSystem->Load("code/compositedataset_cpp.dll");

	gSystem->Load("code/functor_cpp.dll");
	gSystem->Load("code/ppdsdt_cpp.dll");
	gSystem->Load("code/barppdsdt_cpp.dll");
        gSystem->Load("code/PPdsdtTdependentPhase_cpp.dll");

	gSystem->Load("code/Condition_cpp.dll");
	gSystem->Load("code/CompositeCondition_cpp.dll");
	gSystem->Load("code/TRangeCondition_cpp.dll");

	gSystem->Load("code/datasetPPdsdt_cpp.dll");

	gSystem->Load("code/chi2Object_cpp.dll");

	gSystem->Load("code/WriteParametersInfo_cpp.dll");



	gSystem->CompileMacro("Fit.cpp");

	Fit();
}