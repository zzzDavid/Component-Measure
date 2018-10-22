using System;
using System.Collections;
using System.Diagnostics.Eventing.Reader;
using System.Net.Mime;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.ImgHash;
using Emgu.CV.Structure;
using Emgu.CV.Util;

namespace Measurement
{
    public class Measurement
    {
        private Mat _image; // private member _image, accessed or mutated by property Image

        public Mat Image // property member to access/mutate _image
        {
            get { return _image; }
            set
            {
                if (value.Dims != 2)
                    throw new EventLogException("Image mutator only takes a 2-D greyscale Mat.");
                if (value.Cols < 100 || value.Rows < 100)
                    throw new EventLogException("At least 1 dim of the image is too small (< 100px).");
                _image = value;
            }
        }

        public void Load(string filename, double scaling=1.0)
        {
            Mat im = CvInvoke.Imread(filename, ImreadModes.Grayscale);
            Mat imResized = new Mat();
            CvInvoke.Resize(im, imResized, new System.Drawing.Size(0, 0), scaling, scaling, Inter.Cubic);

            _image = imResized;
        }
        
        public Measurement() // constructor
        {
            _image = new Mat();
        }

        public Measurement(string filename) // constructor
        {
            this.Load(filename);
        }
    }
}