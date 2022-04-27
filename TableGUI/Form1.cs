using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace TableGUI
{
    public partial class Form1 : Form
    {
        bool opened = false;
        private SerialPort port = new SerialPort();
        private System.Windows.Forms.Timer aTimer;
        string response = "";

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void aTimer_Tick(object sender, EventArgs e)
        {
            if (port.BytesToRead != 0)
            {
                response = port.ReadExisting();
                lbl_response.Text = response;
                if (response[0] == 'T')
                {
                    lbl_Timer.Text = parseTime(response);
                    lbl_Lscore.Text = parseLeft(response);
                    lbl_Rscore.Text = parseRight(response);
                }
            }
        }


        private void btn_openCOM_Click(object sender, EventArgs e)
        {
            if (!opened) //check if port is already opened
            {
                //open port
                if (COMcomboBox.Text != "")
                {
                    port.PortName = COMcomboBox.Text;
                    port.BaudRate = Convert.ToInt32(txtBaud.Text);
                    port.DtrEnable = true;
                    port.Open();
                    btn_openCOM.Text = "Close COM";
                    btn_openCOM.BackColor = Color.FromArgb(255, 192, 128);
                    opened = true;

                    aTimer = new System.Windows.Forms.Timer();
                    aTimer.Tick += new EventHandler(aTimer_Tick);
                    aTimer.Interval = 50;
                    aTimer.Start();
                }
                
            }
            else
            {
                //close port
                port.Close();
                port.Dispose();
                btn_openCOM.Text = "Open COM";
                btn_openCOM.BackColor = SystemColors.Control;
                opened = false;
                aTimer.Stop();
            }
            
        }

        private void COMcomboBox_DropDown(object sender, EventArgs e)
        {
            COMcomboBox.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
                COMcomboBox.Items.Add(port);
        }

        private void btn_Kill_Click(object sender, EventArgs e)
        {
            if(opened)
                port.Write("k");
        }

        private void btn_clearGUI_Click(object sender, EventArgs e)
        {
            lbl_response.Text = "response";
            lbl_Timer.Text = "0:00";
            lbl_Lscore.Text = "0";
            lbl_Rscore.Text = "0";
        }

        static string parseTime(string input)
        {
            input = input.Remove(input.IndexOf("L"), input.Length - input.IndexOf("L"));
            input = input.Remove(0, 1);
            return input;
        }
        static string parseLeft(string input)
        {
            input = input.Remove(0, input.IndexOf("L") + 1);
            input = input.Remove(input.IndexOf("R"), input.Length - input.IndexOf("R"));
            return input;
        }
        static string parseRight(string input)
        {
            input = input.Remove(0, input.IndexOf("R") + 1);
            return input;
        }

        private void btn_Start_Click(object sender, EventArgs e)
        {
            if (opened)
                port.Write("start");
        }

        private void btn_Pause_Click(object sender, EventArgs e)
        {
            if (opened)
                port.Write("pause");
        }

        private void btn_Resume_Click(object sender, EventArgs e)
        {
            if (opened)
                port.Write("resume");
        }
    }
}
