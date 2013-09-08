void compile()
{
	gSystem->CompileMacro("chi2Object.cpp", "++");

        gSystem->CompileMacro("functor.cpp", "++");
        gSystem->CompileMacro("barppdsdt.cpp", "++");
        gSystem->CompileMacro("ppdsdt.cpp", "++");
        gSystem->CompileMacro("PPdsdtTdependentPhase.cpp", "++");
        gSystem->CompileMacro("PPtot.cpp", "++");

        gSystem->CompileMacro("dataset.cpp", "++");
        gSystem->CompileMacro("compositedataset.cpp", "++");
	gSystem->CompileMacro("datasetPPdsdt.cpp", "++");
	gSystem->CompileMacro("DatasetPPtot.cpp", "++");

	gSystem->CompileMacro("Condition.cpp","++");
	gSystem->CompileMacro("CompositeCondition.cpp","++");
	gSystem->CompileMacro("TRangeCondition.cpp","++");

	gSystem->CompileMacro("WriteParametersInfo.cpp","++");

}
