using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace pm2
{
    public class Background
    {
        public static void DoWork(SerialPort _serialPort)
        {
            while (true)
            {
                string a = _serialPort.ReadExisting();
                if (!string.IsNullOrEmpty(a))
                    Console.WriteLine(a);
                Thread.Sleep(200);
            }
        }
    }
}
