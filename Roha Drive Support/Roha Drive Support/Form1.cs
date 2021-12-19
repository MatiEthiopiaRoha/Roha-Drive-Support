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
using rtChart;

namespace Roha_Drive_Support
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            stopsys.Enabled = false;
            getports();
        }
        kayChart serialDataChart;
        private DateTime datetime;
        void getports()
        {
            String[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
        }

        private void startsys_Click(object sender, EventArgs e)
        {
            try
            {
                if (comboBox1.Text == "" || comboBox2.Text == "")
                {
                    label3.Text = "እባክዎ ፖርት መሙያውን በትክክል ይሙሉ";
                }
                else
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Parity = Parity.None;
                    serialPort1.StopBits = StopBits.One;
                    label3.Text = "ሲስትሙ ተጀምራል";
                    progressBar1.Value = 100;
                    startsys.Enabled = false;
                    stopsys.Enabled = true;
                    serialPort1.Open();
                    serialPort1.DataReceived += new SerialDataReceivedEventHandler(SerialDataReceivedEventHandler);
                    if (!serialPort1.IsOpen)
                    {
                        serialPort1.Open();
                    }
                }
            }

            catch (UnauthorizedAccessException)
            {
                label3.Text = "ያልተፈቀደ ትእዛዝ";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serialDataChart = new kayChart(chart1, 60);

            serialDataChart.serieName = "ርቀት";
        }
        private void SerialDataReceivedEventHandler(object sender, SerialDataReceivedEventArgs e)
        {

            datetime = DateTime.Now;
            SerialPort output = sender as SerialPort;
            string input = output.ReadLine();

            textBox1.Invoke((MethodInvoker)delegate { textBox1.AppendText(datetime + "\t" + "LIDAR Distance" + "\t" + input + "\n"); });
            // initiaization of chart
            double data;
            bool result = Double.TryParse(input, out data);
            if (result)
            {
                serialDataChart.TriggeredUpdate(data);
            }
        }

        private void stopsys_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            label3.Text = "ሲስተሙ ተዘግቷል";
            progressBar1.Value = 0;
            startsys.Enabled = true;
            stopsys.Enabled = false;
        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }
    }
}
