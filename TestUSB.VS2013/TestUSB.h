#pragma once

#include "CmUsbDevice.h"
#include <string>
#include "string.h"
#include "Settings.h"

// Native C++ Klasse
CmUsbDevice DevUSB;

// Target microcontroller settings
#define VID 0x03eb // Vendor ID Atmel
#define PID 0x0001 //  Product ID beliebig

namespace TestUSB
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Zusammenfassung für MyForm
	/// </summary>
	public ref class FormTestUSB : public System::Windows::Forms::Form
	{
	public:
		FormTestUSB(void)
		{
			InitializeComponent();
		}

	protected:
		~FormTestUSB()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BtnClose;
	protected:

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  FilesMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  Exit;


	private: System::Windows::Forms::ToolStripMenuItem^  InfoMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
  private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;

  private: System::Windows::Forms::Label^  label_State;

  private: System::Windows::Forms::TextBox^  textBox_State;
  private: System::Windows::Forms::ProgressBar^  progressBar;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::TextBox^  textBox1;
  private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::ToolStripMenuItem^  OpenDevice;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  TestMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ClaimInterface;

	private: System::Windows::Forms::ToolStripMenuItem^  CloseDevice;
	private: System::Windows::Forms::ToolStripMenuItem^  SendCommand;
	private: System::Windows::Forms::ToolStripMenuItem^  DiscoverDevices;




	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  DiscoverInterfaces;
	private: System::Windows::Forms::ToolStripMenuItem^  ReceiveMessage;
	private: System::Windows::Forms::ToolStripMenuItem^  ReadData;
	private: System::Windows::Forms::ToolStripMenuItem^  WriteData;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;





	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->BtnClose = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->FilesMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OpenDevice = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CloseDevice = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->DiscoverDevices = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DiscoverInterfaces = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->Exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TestMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ClaimInterface = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SendCommand = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ReceiveMessage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ReadData = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WriteData = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->InfoMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label_State = (gcnew System::Windows::Forms::Label());
			this->textBox_State = (gcnew System::Windows::Forms::TextBox());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// BtnClose
			// 
			this->BtnClose->Location = System::Drawing::Point(398, 458);
			this->BtnClose->Name = L"BtnClose";
			this->BtnClose->Size = System::Drawing::Size(75, 23);
			this->BtnClose->TabIndex = 0;
			this->BtnClose->Text = L"Close";
			this->BtnClose->UseVisualStyleBackColor = true;
			this->BtnClose->Click += gcnew System::EventHandler(this, &FormTestUSB::BtnClose_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->FilesMenuItem, this->TestMenuItem,
					this->InfoMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(492, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// FilesMenuItem
			// 
			this->FilesMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->OpenDevice,
					this->CloseDevice, this->toolStripSeparator3, this->DiscoverDevices, this->DiscoverInterfaces, this->toolStripSeparator2, this->toolStripMenuItem1,
					this->toolStripSeparator1, this->Exit
			});
			this->FilesMenuItem->Name = L"FilesMenuItem";
			this->FilesMenuItem->Size = System::Drawing::Size(42, 20);
			this->FilesMenuItem->Text = L"&Files";
			// 
			// OpenDevice
			// 
			this->OpenDevice->Name = L"OpenDevice";
			this->OpenDevice->Size = System::Drawing::Size(173, 22);
			this->OpenDevice->Text = L"&Open Device";
			this->OpenDevice->Click += gcnew System::EventHandler(this, &FormTestUSB::OpenDevice_Click);
			// 
			// CloseDevice
			// 
			this->CloseDevice->Name = L"CloseDevice";
			this->CloseDevice->Size = System::Drawing::Size(173, 22);
			this->CloseDevice->Text = L"&Close Device";
			this->CloseDevice->Click += gcnew System::EventHandler(this, &FormTestUSB::CloseDevice_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(170, 6);
			// 
			// DiscoverDevices
			// 
			this->DiscoverDevices->Name = L"DiscoverDevices";
			this->DiscoverDevices->Size = System::Drawing::Size(173, 22);
			this->DiscoverDevices->Text = L"&Discover Devices";
			this->DiscoverDevices->Click += gcnew System::EventHandler(this, &FormTestUSB::DiscoverDevices_Click);
			// 
			// DiscoverInterfaces
			// 
			this->DiscoverInterfaces->Name = L"DiscoverInterfaces";
			this->DiscoverInterfaces->Size = System::Drawing::Size(173, 22);
			this->DiscoverInterfaces->Text = L"&Discover Interfaces";
			this->DiscoverInterfaces->Click += gcnew System::EventHandler(this, &FormTestUSB::DiscoverInterfaces_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(170, 6);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(173, 22);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(170, 6);
			// 
			// Exit
			// 
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(173, 22);
			this->Exit->Text = L"E&xit";
			this->Exit->Click += gcnew System::EventHandler(this, &FormTestUSB::Exit_Click);
			// 
			// TestMenuItem
			// 
			this->TestMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->ClaimInterface,
					this->toolStripSeparator4, this->SendCommand, this->toolStripMenuItem2, this->toolStripSeparator5, this->ReceiveMessage, this->toolStripSeparator6,
					this->ReadData, this->WriteData
			});
			this->TestMenuItem->Name = L"TestMenuItem";
			this->TestMenuItem->Size = System::Drawing::Size(41, 20);
			this->TestMenuItem->Text = L"&Test";
			// 
			// ClaimInterface
			// 
			this->ClaimInterface->Name = L"ClaimInterface";
			this->ClaimInterface->Size = System::Drawing::Size(163, 22);
			this->ClaimInterface->Text = L"&Claim Interface";
			this->ClaimInterface->Click += gcnew System::EventHandler(this, &FormTestUSB::ClaimInterface_Click);
			// 
			// SendCommand
			// 
			this->SendCommand->Name = L"SendCommand";
			this->SendCommand->Size = System::Drawing::Size(163, 22);
			this->SendCommand->Text = L"&Send Command";
			this->SendCommand->Click += gcnew System::EventHandler(this, &FormTestUSB::SendCommand_Click);
			// 
			// ReceiveMessage
			// 
			this->ReceiveMessage->Name = L"ReceiveMessage";
			this->ReceiveMessage->Size = System::Drawing::Size(163, 22);
			this->ReceiveMessage->Text = L"Receive &Message";
			this->ReceiveMessage->Click += gcnew System::EventHandler(this, &FormTestUSB::ReceiveMessage_Click);
			// 
			// ReadData
			// 
			this->ReadData->Name = L"ReadData";
			this->ReadData->Size = System::Drawing::Size(163, 22);
			this->ReadData->Text = L"&Read Data";
			this->ReadData->Click += gcnew System::EventHandler(this, &FormTestUSB::ReadData_Click);
			// 
			// WriteData
			// 
			this->WriteData->Name = L"WriteData";
			this->WriteData->Size = System::Drawing::Size(163, 22);
			this->WriteData->Text = L"&Write Data";
			this->WriteData->Click += gcnew System::EventHandler(this, &FormTestUSB::WriteData_Click);
			// 
			// InfoMenuItem
			// 
			this->InfoMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->InfoMenuItem->Name = L"InfoMenuItem";
			this->InfoMenuItem->Size = System::Drawing::Size(40, 20);
			this->InfoMenuItem->Text = L"&Info";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"&About";
			// 
			// label_State
			// 
			this->label_State->AutoSize = true;
			this->label_State->Location = System::Drawing::Point(19, 428);
			this->label_State->Name = L"label_State";
			this->label_State->Size = System::Drawing::Size(35, 13);
			this->label_State->TabIndex = 2;
			this->label_State->Text = L"State:";
			// 
			// textBox_State
			// 
			this->textBox_State->Location = System::Drawing::Point(60, 425);
			this->textBox_State->Name = L"textBox_State";
			this->textBox_State->ReadOnly = true;
			this->textBox_State->Size = System::Drawing::Size(414, 20);
			this->textBox_State->TabIndex = 3;
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(60, 379);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(414, 23);
			this->progressBar->Step = 1;
			this->progressBar->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 385);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Progress:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(13, 28);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(467, 334);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Data display";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 232);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Data:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(2, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(45, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Header:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(47, 20);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(414, 206);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"    *** Test USB Device ***";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(47, 232);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(414, 96);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(163, 22);
			this->toolStripMenuItem2->Text = L"&Query Status";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &FormTestUSB::QueryStatus_Click);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(160, 6);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(160, 6);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(160, 6);
			// 
			// WindRecorderDataX
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(492, 494);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->textBox_State);
			this->Controls->Add(this->label_State);
			this->Controls->Add(this->BtnClose);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"WindRecorderDataX";
			this->Text = L"Test USB Device";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//
		// File menu items
		//
private: System::Void OpenDevice_Click(System::Object^  sender, System::EventArgs^  e) {
				 // Open a USB device
					 bool Ret = DevUSB.open_device(VID, PID);
					 String^ Msg = gcnew String("");
					 if (Ret){
						 Msg = "\r\n opened USB device VID=" + VID + " PID=" + PID;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 Msg = "\r\n opening USB device VID=" + VID + " PID=" + PID + " failed.";
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void CloseDevice_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Close USB device
					 bool Ret = DevUSB.close_device();
					 if (Ret){
						 this->textBox1->Text = L"    *** Test USB Device ***";
					 }
					 else{
						 String^ Msg = gcnew String("");
						 Msg = "\r\n closing USB device failed.";
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void DiscoverDevices_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Discover devices 
					 CmString Devices;
					 int Ret = DevUSB.discover_devices(Devices);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n discover_device_interfaces: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 CmString Info = Devices;
						 String^ Msg = gcnew String(Info.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void DiscoverInterfaces_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Discover a device's interfaces
					 CmString Interfaces;
					 int Ret = DevUSB.discover_interface(VID,PID,Interfaces);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n discover_device_interfaces: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 CmString Info = Interfaces;
						 String^ Msg = gcnew String(Info.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e) {
					 Close();
}

				 //
				 // Test menu items
				 //
private: System::Void ClaimInterface_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Claim interfaces
					 String^ Msg = gcnew String("");
					 const int LastInterface = 0;
					 for (int i = LastInterface; i >= 0; i--){
						 bool Ret = DevUSB.claim_interface(i);
						 if (Ret){
							 Msg = "\r\n claimed interface " + i;
							 this->textBox1->AppendText(Msg);
						 }
						 else{
							 Msg = "\r\n claiming interface " + i + " failed";
							 this->textBox1->AppendText(Msg);
						 }
					 }
}
private: System::Void SendCommand_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Send a command to USB device 
					 CmString Command;  // length = 0 byte
					 //sprintf(Command.getBuffer(), "EP0.send.command........");
					 RequestCode Request = SET_FEATURE;
					 int Value = 12345;
					 int Index = 999;
					 int Ret = DevUSB.send_command(REQ_TYPE_VENDOR, REQ_RECP_DEVICE, Command, Request, Value, Index);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n send_command: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 int Req = (int)Request;
						 String^ Msg = "\r\n send_command:  req: " + Req + "  val: " + Value + "  idx: " + Index + "  cmd: " + gcnew String(Command.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void QueryStatus_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Query status
					 CmString Status(64);
					 RequestCode Request = GET_STATUS;
					 int Value = 67890;
					 int Index = 111;
					 int Ret = DevUSB.query_status(REQ_TYPE_VENDOR, REQ_RECP_DEVICE, Status, Request, Value, Index);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n query_status: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 int Req = (int)Request;
						 String^ Msg = "\r\n query_status:  req: " + Req + "  val: " + Value + "  idx: " + Index + "  status: " + gcnew String(Status.getText());;
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void ReceiveMessage_Click(System::Object^  sender, System::EventArgs^  e) {
					 // Receive a message 
					 int8 Endpoint = 129;
					 CmString Message(262144);
					 double TransferRate;
					 int32 Transferred;
					 int Ret = DevUSB.transfer_data(Endpoint, Message.getBuffer(), Message.getLength(), &Transferred, &TransferRate);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n read_data: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 CmString Info = Message;
						 CmString InfoReduced;
						 InfoReduced.assignSubString(32, &Message);
						 int Rate_kB = (int)(TransferRate / 1000);
						 String^ Msg = "\r\n Message: read_data (" + Transferred + " bytes/" + Rate_kB + " kB/s): " + gcnew String(InfoReduced.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void ReadData_Click(System::Object^  sender, System::EventArgs^  e) {
					 // read binary data
					 int8 Endpoint = 130;
					 CmString Message(262144);
					 double TransferRate;
					 int32 Transferred;
					 int Ret = DevUSB.transfer_data(Endpoint, Message.getBuffer(), Message.getLength(), &Transferred, &TransferRate);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n read_data: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 CmString Info = Message;
						 CmString InfoReduced;
						 InfoReduced.assignSubString(32, &Message);
						 int Rate_kB = (int)(TransferRate / 1000);
						 String^ Msg = "\r\n Data: read_data (" + Transferred + " bytes/" + Rate_kB + " kB/s): " + gcnew String(InfoReduced.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
private: System::Void WriteData_Click(System::Object^  sender, System::EventArgs^  e) {
					 // write binary data
					 int8 Endpoint = 3;
					 CmString Message(262144);
					 sprintf(Message.getBuffer(), "EP3:.write.data........................");
					 double TransferRate;
					 int32 Transferred;
					 int Ret = DevUSB.transfer_data(Endpoint, Message.getBuffer(), Message.getLength(), &Transferred, &TransferRate);
					 if (Ret != LIBUSB_SUCCESS){
						 String^ Msg = gcnew String(DevUSB.getErrorString(Ret).getText());
						 Msg = "\r\n write_data: " + Msg;
						 this->textBox1->AppendText(Msg);
					 }
					 else{
						 CmString Info = Message;
						 CmString InfoReduced;
						 InfoReduced.assignSubString(32, &Message);
						 int Rate_kB = (int)(TransferRate / 1000);
						 String^ Msg = "\r\n Data: write_data (" + Transferred + " bytes/" + Rate_kB + " kB/s): " + gcnew String(InfoReduced.getText());
						 this->textBox1->AppendText(Msg);
					 }
}
				 //
				 // Button functions
				 //
private: System::Void BtnClose_Click(System::Object^  sender, System::EventArgs^  e) {
					 Close();
}
};
}
