using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Client
{
    public partial class Form1 : Form
    {
        public const uint WM_COPYDATA = 0x004a;
 
        [StructLayout(LayoutKind.Sequential)]
        public struct COPYDATASTRUCT
        {

            [MarshalAs(UnmanagedType.I4)]
            public int dwData;
            [MarshalAs(UnmanagedType.I4)]
            public int cbData;
            [MarshalAs(UnmanagedType.SysInt)]
            public IntPtr lpData;
        }

        [DllImport("User32.dll")]
        private static extern bool SendMessage(IntPtr hWnd,uint wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        Process m_maple;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.m_maple = Process.GetProcessesByName("MapleStory")[0];
        }

        private void SendString(IntPtr wnd)
        {
            string s = "hi2server" +  char.MinValue;
            IntPtr lpData = Marshal.StringToHGlobalAnsi(s);
 
            COPYDATASTRUCT data = new COPYDATASTRUCT();
            data.dwData = 0;
            data.cbData = s.Length + 1;
            data.lpData = lpData;
 
            IntPtr lpStruct = Marshal.AllocHGlobal(Marshal.SizeOf(data));
 
            Marshal.StructureToPtr(data, lpStruct, false);
            SendMessage(wnd, WM_COPYDATA,this.Handle, lpStruct);
        }

        
        private void button2_Click(object sender, EventArgs e)
        {
            IntPtr n = FindWindow(null, "MapleStory");
            if (n != IntPtr.Zero)
                SendString(n);
            else
                MessageBox.Show("Window not found");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Text = this.m_maple.MainWindowTitle + " PID: " + this.m_maple.Id.ToString(("X4"));
        }
    }
}
