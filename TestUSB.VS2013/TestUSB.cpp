#include "TestUSB.h" //the header name for your form

using namespace TestUSB; //the project name in your header file

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  // check whether command line arguments have been passed
  if (args->Length == 0)
  {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false); 

		Application::Run(gcnew FormTestUSB());
  }
  else
  {
    // Determine number of args
    int ArgCount = args->Length;

    // display a helpscreen
	// NOTE: A console window might not be activated
    if (ArgCount > 0 && args[0]->Contains("--help")) {
      Console::WriteLine("App v1.0");
      Console::ReadLine();
    }
    else
    {
      // Transfer command line arguments to function parameters
      if (ArgCount > 0) {
        char* ptrStartTime = (char*)Marshal::StringToHGlobalAnsi(args[0]).ToPointer();
        // using: ptrStartTime;
        Marshal::FreeHGlobal(IntPtr(ptrStartTime));
      }
    }
  }
}

