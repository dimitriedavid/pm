using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pm2
{
    public partial class Form1 : Form
    {
        static SerialPort _serialPort;

        public Form1()
        {
            InitializeComponent();

            _serialPort = new SerialPort();
            _serialPort.PortName = "COM4";
            _serialPort.BaudRate = 9600;
            _serialPort.WriteBufferSize = 2;
            _serialPort.Open();

            Thread thread = new Thread(() => Background.DoWork(_serialPort));
            thread.Start();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Left)
                _serialPort.Write("l");
            else if (e.KeyCode == Keys.Right)
                _serialPort.Write("r");
            else if (e.KeyCode == Keys.Up)
                _serialPort.Write("d");
            else if (e.KeyCode == Keys.Down)
                _serialPort.Write("u");
            else if (e.KeyCode == Keys.Space)
                _serialPort.Write("s");
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            _serialPort.Close();
        }
    }
}
