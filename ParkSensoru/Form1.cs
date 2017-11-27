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
using System.Drawing;

namespace ParkSensoru
{
    public partial class Form1 : Form
    {
        public SerialPort myport;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                connect(portlist.SelectedItem.ToString());
                timer2.Start();
            }
            catch
            {
                MessageBox.Show("select COM port first");
            }
        }
        private void connect(string portname)
        {
            myport = new SerialPort();
            myport.BaudRate = 9600;
            myport.PortName = portname;
            myport.Parity = Parity.None;
            myport.DataBits = 8;
            myport.StopBits = StopBits.One;
            myport.Handshake = Handshake.None;
            myport.Encoding = System.Text.Encoding.Default;
            myport.DataReceived += myport_DataReceived;
            try
            {
                myport.Open();
                label1.Visible = true;
                label1.Text = portname;
                System.Threading.Thread.Sleep(2000);
            }
            catch
            {
                MessageBox.Show("error check connection or port name");
            }
        }
        private void getserialnames()
        {
            portlist.Items.Clear();
            foreach (string sp in SerialPort.GetPortNames())
            {
                portlist.Items.Add(sp);
            }
        }
        private string in_data;
       // private int in_data;
        private void myport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            in_data = myport.ReadLine();

            this.Invoke(new EventHandler(event_action));

        }
        
        int i = 0;

        int value;
        string[] token = new string[2];
        private void event_action(object sender, EventArgs e)
        {
            token = in_data.Split('/');
            foreach (string tokens in token)
            {
                if (i == 0)
                {
                    value = Convert.ToInt32(token[0]);
                    label4.Text = value.ToString();
                    on.Width = (280 * (100-value)) / 100;
                    on.Height = 221;
                    if (value < 20) timer3.Start();
                    else {
                        timer3.Stop();
                        if (on.Visible == true) on.Visible = false;
                        if (on.Visible == false) on.Visible = true;
                    }
                    }

                if (i == 1)
                {
                    
                    value = Convert.ToInt32(token[1]);
                    label5.Text = value.ToString();
                    pictureBox4.Width = ((250 * (100-value)) /100);
                    pictureBox4.Location = new Point(900 - ((250 * (100-value)) / 100), 300);

                    if (value >= 68 && value <= 100)
                    {
                        changeImage(value);
                        pictureBox4.Image = Image.FromFile(@"Images\yesilarka.png");
                        timer1.Stop();
                        if (pictureBox4.Visible == true) pictureBox4.Visible = false;
                        if (pictureBox4.Visible == false) pictureBox4.Visible = true;
                    }
                    if (value >= 34 && value <= 67)
                    {
                        pictureBox4.Image = Image.FromFile(@"Images\turuncuarka.png");
                        timer1.Stop();
                        if (pictureBox4.Visible == true) pictureBox4.Visible = false;
                        if (pictureBox4.Visible == false) pictureBox4.Visible = true;
                    }
                    if (value > 0 && value <= 33)
                    {
                        pictureBox4.Image = Image.FromFile(@"Images\kırmızıarka.png");
                        if(value < 20) timer1.Start();
                        
                    }
                }
              
                i++;
            }
            i = 0;
        }
        public static Bitmap RotateImage(Image image, PointF offset, float angle)
        {
            if (image == null)
                throw new ArgumentNullException("image");

            //create a new empty bitmap to hold rotated image
            Bitmap rotatedBmp = new Bitmap(image.Width, image.Height);
            rotatedBmp.SetResolution(image.HorizontalResolution, image.VerticalResolution);

            //make a graphics object from the empty bitmap
            Graphics g = Graphics.FromImage(rotatedBmp);

            //Put the rotation point in the center of the image
            g.TranslateTransform(offset.X, offset.Y);

            //rotate the image
            g.RotateTransform(angle);

            //move the image back
            g.TranslateTransform(-offset.X, -offset.Y);

            //draw passed in image onto graphics object
            g.DrawImage(image, new PointF(0, 0));

            return rotatedBmp;
        }
        void changeImage(int degree)
        {
            //Load an image in from a file
            Image image = new Bitmap(@"Images\arrows.png");
            //Set our picture box to that image
            pictureBox2.Image = (Bitmap)image.Clone();

            //Store our old image so we can delete it
            Image oldImage = pictureBox2.Image;
            //Pass in our original image and return a new image rotated 35 degrees right
            pictureBox2.Image = RotateImage(image,new PointF(400, 400), degree);
            if (oldImage != null)
            {
                oldImage.Dispose();
            } 
        }
        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            getserialnames();
        /*    yesilLeft.Visible = false;
            turuncuLeft.Visible = false;
            kirmiziLeft.Visible = false;

            a1.Visible = false;
            a2.Visible = false;
            a3.Visible = false;*/

        }
        int counter = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (counter % 2 == 0) pictureBox4.Visible = false;
            if (counter % 2 == 1) pictureBox4.Visible = true;
            counter++;
            
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            this.Invoke(new EventHandler(event_action));
        }
        int counter2 = 0;
        private void timer3_Tick(object sender, EventArgs e)
        {
            if (counter2 % 2 == 0) on.Visible = false;
            if (counter2 % 2 == 1) on.Visible = true;
            counter2++;
        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

      
    }
}
