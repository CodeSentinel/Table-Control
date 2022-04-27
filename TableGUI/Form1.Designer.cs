﻿
namespace TableGUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.COMcomboBox = new System.Windows.Forms.ComboBox();
            this.btn_openCOM = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtBaud = new System.Windows.Forms.TextBox();
            this.btn_Kill = new System.Windows.Forms.Button();
            this.btn_clearGUI = new System.Windows.Forms.Button();
            this.lbl_Timer = new System.Windows.Forms.Label();
            this.lbl_Lscore = new System.Windows.Forms.Label();
            this.lbl_Rscore = new System.Windows.Forms.Label();
            this.lbl_response = new System.Windows.Forms.Label();
            this.btn_Start = new System.Windows.Forms.Button();
            this.btn_Pause = new System.Windows.Forms.Button();
            this.btn_Resume = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // COMcomboBox
            // 
            this.COMcomboBox.ForeColor = System.Drawing.SystemColors.WindowText;
            this.COMcomboBox.FormattingEnabled = true;
            this.COMcomboBox.Location = new System.Drawing.Point(228, 46);
            this.COMcomboBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.COMcomboBox.Name = "COMcomboBox";
            this.COMcomboBox.Size = new System.Drawing.Size(108, 32);
            this.COMcomboBox.TabIndex = 1;
            this.COMcomboBox.DropDown += new System.EventHandler(this.COMcomboBox_DropDown);
            // 
            // btn_openCOM
            // 
            this.btn_openCOM.BackColor = System.Drawing.SystemColors.Control;
            this.btn_openCOM.Location = new System.Drawing.Point(23, 44);
            this.btn_openCOM.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_openCOM.Name = "btn_openCOM";
            this.btn_openCOM.Size = new System.Drawing.Size(128, 39);
            this.btn_openCOM.TabIndex = 2;
            this.btn_openCOM.Text = "Open COM";
            this.btn_openCOM.UseVisualStyleBackColor = false;
            this.btn_openCOM.Click += new System.EventHandler(this.btn_openCOM_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(168, 51);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 25);
            this.label1.TabIndex = 3;
            this.label1.Text = "Port:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(342, 51);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 25);
            this.label2.TabIndex = 4;
            this.label2.Text = "Baud:";
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(412, 50);
            this.txtBaud.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(84, 29);
            this.txtBaud.TabIndex = 5;
            this.txtBaud.Text = "9600";
            // 
            // btn_Kill
            // 
            this.btn_Kill.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.btn_Kill.Location = new System.Drawing.Point(187, 172);
            this.btn_Kill.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_Kill.Name = "btn_Kill";
            this.btn_Kill.Size = new System.Drawing.Size(151, 75);
            this.btn_Kill.TabIndex = 6;
            this.btn_Kill.Text = "Kill Game";
            this.btn_Kill.UseVisualStyleBackColor = false;
            this.btn_Kill.Click += new System.EventHandler(this.btn_Kill_Click);
            // 
            // btn_clearGUI
            // 
            this.btn_clearGUI.Location = new System.Drawing.Point(346, 92);
            this.btn_clearGUI.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_clearGUI.Name = "btn_clearGUI";
            this.btn_clearGUI.Size = new System.Drawing.Size(151, 75);
            this.btn_clearGUI.TabIndex = 7;
            this.btn_clearGUI.Text = "Clear GUI";
            this.btn_clearGUI.UseVisualStyleBackColor = true;
            this.btn_clearGUI.Click += new System.EventHandler(this.btn_clearGUI_Click);
            // 
            // lbl_Timer
            // 
            this.lbl_Timer.AutoSize = true;
            this.lbl_Timer.Font = new System.Drawing.Font("Microsoft Sans Serif", 79.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_Timer.Location = new System.Drawing.Point(1020, 388);
            this.lbl_Timer.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_Timer.Name = "lbl_Timer";
            this.lbl_Timer.Size = new System.Drawing.Size(453, 211);
            this.lbl_Timer.TabIndex = 8;
            this.lbl_Timer.Text = "0:00";
            // 
            // lbl_Lscore
            // 
            this.lbl_Lscore.AutoSize = true;
            this.lbl_Lscore.Font = new System.Drawing.Font("Microsoft Sans Serif", 79.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_Lscore.Location = new System.Drawing.Point(324, 944);
            this.lbl_Lscore.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_Lscore.Name = "lbl_Lscore";
            this.lbl_Lscore.Size = new System.Drawing.Size(193, 211);
            this.lbl_Lscore.TabIndex = 9;
            this.lbl_Lscore.Text = "0";
            // 
            // lbl_Rscore
            // 
            this.lbl_Rscore.AutoSize = true;
            this.lbl_Rscore.Font = new System.Drawing.Font("Microsoft Sans Serif", 79.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_Rscore.Location = new System.Drawing.Point(1992, 944);
            this.lbl_Rscore.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_Rscore.Name = "lbl_Rscore";
            this.lbl_Rscore.Size = new System.Drawing.Size(193, 211);
            this.lbl_Rscore.TabIndex = 10;
            this.lbl_Rscore.Text = "0";
            // 
            // lbl_response
            // 
            this.lbl_response.AutoSize = true;
            this.lbl_response.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_response.Location = new System.Drawing.Point(23, 252);
            this.lbl_response.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_response.Name = "lbl_response";
            this.lbl_response.Size = new System.Drawing.Size(89, 24);
            this.lbl_response.TabIndex = 11;
            this.lbl_response.Text = "response";
            // 
            // btn_Start
            // 
            this.btn_Start.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.btn_Start.Location = new System.Drawing.Point(28, 92);
            this.btn_Start.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_Start.Name = "btn_Start";
            this.btn_Start.Size = new System.Drawing.Size(151, 75);
            this.btn_Start.TabIndex = 12;
            this.btn_Start.Text = "Start";
            this.btn_Start.UseVisualStyleBackColor = false;
            this.btn_Start.Click += new System.EventHandler(this.btn_Start_Click);
            // 
            // btn_Pause
            // 
            this.btn_Pause.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.btn_Pause.Location = new System.Drawing.Point(28, 172);
            this.btn_Pause.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_Pause.Name = "btn_Pause";
            this.btn_Pause.Size = new System.Drawing.Size(151, 75);
            this.btn_Pause.TabIndex = 13;
            this.btn_Pause.Text = "Pause";
            this.btn_Pause.UseVisualStyleBackColor = false;
            this.btn_Pause.Click += new System.EventHandler(this.btn_Pause_Click);
            // 
            // btn_Resume
            // 
            this.btn_Resume.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.btn_Resume.Location = new System.Drawing.Point(187, 92);
            this.btn_Resume.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btn_Resume.Name = "btn_Resume";
            this.btn_Resume.Size = new System.Drawing.Size(151, 75);
            this.btn_Resume.TabIndex = 14;
            this.btn_Resume.Text = "Resume";
            this.btn_Resume.UseVisualStyleBackColor = false;
            this.btn_Resume.Click += new System.EventHandler(this.btn_Resume_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 60F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(98, 774);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(704, 159);
            this.label3.TabIndex = 15;
            this.label3.Text = "Left Score";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 60F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(1698, 774);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(797, 159);
            this.label4.TabIndex = 16;
            this.label4.Text = "Right Score";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 60F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(1055, 219);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(379, 159);
            this.label5.TabIndex = 17;
            this.label5.Text = "Time";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.Color.Gold;
            this.label6.Location = new System.Drawing.Point(2384, 14);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(187, 54);
            this.label6.TabIndex = 18;
            this.label6.Text = "CPPRC";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_openCOM);
            this.groupBox1.Controls.Add(this.lbl_response);
            this.groupBox1.Controls.Add(this.COMcomboBox);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.btn_Resume);
            this.groupBox1.Controls.Add(this.txtBaud);
            this.groupBox1.Controls.Add(this.btn_Pause);
            this.groupBox1.Controls.Add(this.btn_clearGUI);
            this.groupBox1.Controls.Add(this.btn_Start);
            this.groupBox1.Controls.Add(this.btn_Kill);
            this.groupBox1.Location = new System.Drawing.Point(16, 18);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Size = new System.Drawing.Size(525, 342);
            this.groupBox1.TabIndex = 19;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Controls";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2560, 1400);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbl_Rscore);
            this.Controls.Add(this.lbl_Lscore);
            this.Controls.Add(this.lbl_Timer);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "TableUI";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox COMcomboBox;
        private System.Windows.Forms.Button btn_openCOM;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtBaud;
        private System.Windows.Forms.Button btn_Kill;
        private System.Windows.Forms.Button btn_clearGUI;
        private System.Windows.Forms.Label lbl_Timer;
        private System.Windows.Forms.Label lbl_Lscore;
        private System.Windows.Forms.Label lbl_Rscore;
        private System.Windows.Forms.Label lbl_response;
        private System.Windows.Forms.Button btn_Start;
        private System.Windows.Forms.Button btn_Pause;
        private System.Windows.Forms.Button btn_Resume;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

