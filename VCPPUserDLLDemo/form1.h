#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace VCPPUserDLLDemo {

	/// <summary>
	/// Zusammenfassung f�r form1
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse �ndern, m�ssen Sie auch
	///          die Ressourcendateiname-Eigenschaft f�r das Tool zur Kompilierung verwalteter Ressourcen �ndern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abh�ngt.
	///          Anderenfalls k�nnen die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class form1 : public System::Windows::Forms::Form
	{
	public:
		form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzuf�gen.
			//
		}
	public: 
		void seta(double value){
			atextBox->Text = value.ToString();
			}
		void setb(double value){
			btextBox->Text = value.ToString();
			}
		double geta(){
			return Double::Parse(atextBox->Text);
			}
		double getb(){
			return Double::Parse(btextBox->Text);
			}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  btextBox;
	private: System::Windows::Forms::TextBox^  atextBox;
	private: System::Windows::Forms::Label^  blabel;
	private: System::Windows::Forms::Label^  alabel;
	private: System::Windows::Forms::Button^  okBtn;
	private: System::Windows::Forms::Button^  cancelBtn;
	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btextBox = (gcnew System::Windows::Forms::TextBox());
			this->atextBox = (gcnew System::Windows::Forms::TextBox());
			this->blabel = (gcnew System::Windows::Forms::Label());
			this->alabel = (gcnew System::Windows::Forms::Label());
			this->okBtn = (gcnew System::Windows::Forms::Button());
			this->cancelBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btextBox);
			this->groupBox1->Controls->Add(this->atextBox);
			this->groupBox1->Controls->Add(this->blabel);
			this->groupBox1->Controls->Add(this->alabel);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 94);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Parameter";
			// 
			// btextBox
			// 
			this->btextBox->Location = System::Drawing::Point(40, 54);
			this->btextBox->Name = L"btextBox";
			this->btextBox->Size = System::Drawing::Size(100, 20);
			this->btextBox->TabIndex = 3;
			// 
			// atextBox
			// 
			this->atextBox->Location = System::Drawing::Point(40, 29);
			this->atextBox->Name = L"atextBox";
			this->atextBox->Size = System::Drawing::Size(99, 20);
			this->atextBox->TabIndex = 2;
			// 
			// blabel
			// 
			this->blabel->AutoSize = true;
			this->blabel->Location = System::Drawing::Point(18, 57);
			this->blabel->Name = L"blabel";
			this->blabel->Size = System::Drawing::Size(16, 13);
			this->blabel->TabIndex = 1;
			this->blabel->Text = L"b:";
			// 
			// alabel
			// 
			this->alabel->AutoSize = true;
			this->alabel->Location = System::Drawing::Point(18, 32);
			this->alabel->Name = L"alabel";
			this->alabel->Size = System::Drawing::Size(16, 13);
			this->alabel->TabIndex = 0;
			this->alabel->Text = L"a:";
			// 
			// okBtn
			// 
			this->okBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okBtn->Location = System::Drawing::Point(218, 12);
			this->okBtn->Name = L"okBtn";
			this->okBtn->Size = System::Drawing::Size(75, 23);
			this->okBtn->TabIndex = 1;
			this->okBtn->Text = L"OK";
			this->okBtn->UseVisualStyleBackColor = true;
			// 
			// cancelBtn
			// 
			this->cancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelBtn->Location = System::Drawing::Point(218, 41);
			this->cancelBtn->Name = L"cancelBtn";
			this->cancelBtn->Size = System::Drawing::Size(75, 23);
			this->cancelBtn->TabIndex = 2;
			this->cancelBtn->Text = L"Abbrechen";
			this->cancelBtn->UseVisualStyleBackColor = true;
			// 
			// form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelBtn;
			this->ClientSize = System::Drawing::Size(300, 118);
			this->Controls->Add(this->cancelBtn);
			this->Controls->Add(this->okBtn);
			this->Controls->Add(this->groupBox1);
			this->Name = L"form1";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Demo-Dialog";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
