#pragma once

namespace TestUSB {

	using namespace System;
  using namespace System::Configuration;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Settings
	/// </summary>
	public ref class Settings : public System::Windows::Forms::Form
	{

    //Application settings wrapper class
    ref class FormSettings sealed: public ApplicationSettingsBase
    {
    public:
        [UserScopedSettingAttribute()]
        [DefaultSettingValueAttribute("C:\\DataX\\")]
        property String^ DataXroot
        {
            String^ get()
            {
                return (String^)this["DataXroot"];
            }
            void set( String^ value )
            {
                this["DataXroot"] = value;
            }
        }

    public:
        [UserScopedSettingAttribute()]
        [DefaultSettingValueAttribute("<operator>")]
        property String^ Operator
        {
            String^ get()
            {
                return (String^)this["Operator"];
            }
            void set( String^ value )
            {
                this["Operator"] = value;
            }
        }

    public:
        [UserScopedSettingAttribute()]
        [DefaultSettingValueAttribute("<locator_city>")]
        property String^ Location
        {
            String^ get()
            {
                return (String^)this["Location"];
            }
            void set( String^ value )
            {
                this["Location"] = value;
            }
        }

    public:
        [UserScopedSettingAttribute()]
        [DefaultSettingValueAttribute("WindRecorder")]
        property String^ Equipment
        {
            String^ get()
            {
                return (String^)this["Equipment"];
            }
            void set( String^ value )
            {
                this["Equipment"] = value;
            }
        }
    };

	public:
		Settings(void)
		{
      // Create form settings
      formSettings = gcnew FormSettings;

			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Settings()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::Button^  button1;
  protected: 
  private: System::Windows::Forms::Button^  button2;
  public: System::Windows::Forms::TextBox^  textBox_DataXroot;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label4;
  public: System::Windows::Forms::TextBox^  textBox_Operator;
  public: System::Windows::Forms::TextBox^  textBox_Location;
  public: System::Windows::Forms::TextBox^  textBox_Equipment;
  private: System::Windows::Forms::Label^  label5;
  public: 
  private: System::Windows::Forms::Label^  label6;
  private: System::Windows::Forms::Label^  label7;
  private: System::Windows::Forms::Label^  label8;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

  private:
    FormSettings ^ formSettings;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->textBox_DataXroot = (gcnew System::Windows::Forms::TextBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->textBox_Operator = (gcnew System::Windows::Forms::TextBox());
      this->textBox_Location = (gcnew System::Windows::Forms::TextBox());
      this->textBox_Equipment = (gcnew System::Windows::Forms::TextBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // button1
      // 
      this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->button1->Location = System::Drawing::Point(290, 240);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(75, 23);
      this->button1->TabIndex = 0;
      this->button1->Text = L"Cancel";
      this->button1->UseVisualStyleBackColor = true;
      // 
      // button2
      // 
      this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->button2->Location = System::Drawing::Point(209, 240);
      this->button2->Name = L"button2";
      this->button2->Size = System::Drawing::Size(75, 23);
      this->button2->TabIndex = 1;
      this->button2->Text = L"OK";
      this->button2->UseVisualStyleBackColor = true;
      // 
      // textBox_DataXroot
      // 
      this->textBox_DataXroot->Location = System::Drawing::Point(83, 13);
      this->textBox_DataXroot->Name = L"textBox_DataXroot";
      this->textBox_DataXroot->Size = System::Drawing::Size(261, 20);
      this->textBox_DataXroot->TabIndex = 2;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(14, 16);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(61, 13);
      this->label1->TabIndex = 3;
      this->label1->Text = L"DataX root:";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(24, 45);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(51, 13);
      this->label2->TabIndex = 4;
      this->label2->Text = L"Operator:";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(24, 75);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(51, 13);
      this->label3->TabIndex = 5;
      this->label3->Text = L"Location:";
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point(15, 105);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(60, 13);
      this->label4->TabIndex = 6;
      this->label4->Text = L"Equipment:";
      // 
      // textBox_Operator
      // 
      this->textBox_Operator->Location = System::Drawing::Point(81, 42);
      this->textBox_Operator->Name = L"textBox_Operator";
      this->textBox_Operator->Size = System::Drawing::Size(134, 20);
      this->textBox_Operator->TabIndex = 7;
      // 
      // textBox_Location
      // 
      this->textBox_Location->Location = System::Drawing::Point(83, 72);
      this->textBox_Location->Name = L"textBox_Location";
      this->textBox_Location->Size = System::Drawing::Size(132, 20);
      this->textBox_Location->TabIndex = 8;
      // 
      // textBox_Equipment
      // 
      this->textBox_Equipment->Location = System::Drawing::Point(83, 102);
      this->textBox_Equipment->Name = L"textBox_Equipment";
      this->textBox_Equipment->Size = System::Drawing::Size(132, 20);
      this->textBox_Equipment->TabIndex = 9;
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(17, 137);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(281, 13);
      this->label5->TabIndex = 10;
      this->label5->Text = L"DataX root: choose your repository root (e.g. \"C:\\DataX\\\")";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Location = System::Drawing::Point(17, 161);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(344, 13);
      this->label6->TabIndex = 11;
      this->label6->Text = L"Operator: name, place of birth (like \"EKD\" for Eckhard Kantz Dambeck)";
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Location = System::Drawing::Point(17, 185);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(251, 13);
      this->label7->TabIndex = 12;
      this->label7->Text = L"Location: locator + city (e.g. \"JN58nc_Türkenfeld\") ";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Location = System::Drawing::Point(17, 209);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(268, 13);
      this->label8->TabIndex = 13;
      this->label8->Text = L"Equipment: hardware equipment (e.g. \"WindRecorder\")";
      // 
      // Settings
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(380, 275);
      this->ControlBox = false;
      this->Controls->Add(this->label8);
      this->Controls->Add(this->label7);
      this->Controls->Add(this->label6);
      this->Controls->Add(this->label5);
      this->Controls->Add(this->textBox_Equipment);
      this->Controls->Add(this->textBox_Location);
      this->Controls->Add(this->textBox_Operator);
      this->Controls->Add(this->label4);
      this->Controls->Add(this->label3);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->textBox_DataXroot);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->MaximizeBox = false;
      this->MinimizeBox = false;
      this->Name = L"Settings";
      this->Text = L"Settings";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Settings::Settings_FormClosing);
      this->Load += gcnew System::EventHandler(this, &Settings::Settings_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void Settings_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
             // Synchronize settings
             formSettings->DataXroot = textBox_DataXroot->Text;
             formSettings->Operator = textBox_Operator->Text;
             formSettings->Location = textBox_Location->Text;
             formSettings->Equipment = textBox_Equipment->Text;
             formSettings->Save();
           }
private: System::Void Settings_Load(System::Object^  sender, System::EventArgs^  e) {
           // Load settings
           textBox_DataXroot->Text = formSettings->DataXroot;
           textBox_Operator->Text = formSettings->Operator;
           textBox_Location->Text = formSettings->Location;
           textBox_Equipment->Text = formSettings->Equipment;

         }
};
}
