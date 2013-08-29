void draw()
{

	gSystem->Load("code/functor_cpp.dll");
	gSystem->Load("code/ppdsdt_cpp.dll");
	gSystem->Load("code/barppdsdt_cpp.dll");
        gSystem->Load("code/PPdsdtTdependentPhase_cpp.dll");


	gSystem->CompileMacro("Plot.cpp");

	Fit();
}