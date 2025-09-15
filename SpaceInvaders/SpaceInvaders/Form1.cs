using System.ComponentModel;
using System.Timers;

namespace SpaceInvaders
{
    public partial class Form1 : Form
    {
        private BackgroundWorker _bwGameLogic;
        private Tank _tank;
        private Invaders _invaders;

        public Form1()
        {
            InitializeComponent();

            Name = "Space Invaders";
            Text = "Space Invaders";
            Size = new(100, 750);
            MinimumSize = new(880, 480);
            FormBorderStyle = FormBorderStyle.Fixed3D;
            DoubleBuffered = true;
            Paint += Form1_Paint;
            KeyDown += Form1_KeyDown;

            _bwGameLogic = new();
            _bwGameLogic.DoWork += RunGameLogic;

            _tank = new(0, Height - 96);
            _invaders = new();
        }

        private void Form1_KeyDown(object? sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Left:
                case Keys.A:
                    _tank.Body.X = _tank.Body.X - Tank.Speed > 0 ? _tank.Body.X - Tank.Speed : Width;
                    break;
                case Keys.Right:
                case Keys.D:
                    _tank.Body.X = _tank.Body.X + Tank.Speed < Width ? _tank.Body.X + Tank.Speed : 0;
                    break;
                case Keys.Space:
                    if (!_tank.BulletShot)
                    {
                        _tank.BulletShot = true;
                        _tank.Bullet.X = _tank.Body.X + ((_tank.Body.Width / 2) - (_tank.Bullet.Width / 2));
                        _tank.Bullet.Y = _tank.Body.Y;
                    }
                    break;
            }

            Invalidate();
        }

        private void Form1_Paint(object? sender, PaintEventArgs e)
        {
            e.Graphics.Clear(Color.Black);

            foreach (var invader in _invaders.InvadersBodies)
                e.Graphics.FillRectangle(Brushes.Red, invader);

            e.Graphics.FillRectangle(Brushes.Green, _tank.Body);
            if (_tank.BulletShot)
                e.Graphics.FillRectangle(Brushes.LightGreen, _tank.Bullet);
        }

        private void Form1_Load(object? sender, EventArgs e) => _bwGameLogic.RunWorkerAsync();

        private void RunGameLogic(object? sender, DoWorkEventArgs e)
        {
            while (!_invaders.AtBottom)
            {
                if (_tank.BulletShot)
                {
                    if (_tank.Bullet.Y > 0 && !_invaders.HasBulletHit(_tank.Bullet))
                        _tank.Bullet.Y -= Tank.BulletSpeed;
                    else
                        _tank.BulletShot = false;
                }

                Invalidate();
                Thread.Sleep(1);
            }
        }
    }

    internal class Tank
    {
        public const int Speed = 10;

        public const int BulletSpeed = 20;
        public const int BulletDamage = 5;

        public Rectangle Body;
        public Rectangle Bullet;
        public bool BulletShot;

        public Tank(int x, int y) 
        {
            Body = new(x, y, 32, 16);
            Bullet = new(x, y, 8, 8);
            BulletShot = false;
        }
    }

    internal class Invaders
    {
        public const int Width = 10;
        public const int Height = 3;

        public int X;
        public int Y;
        public int XDirection;
        public Rectangle[] InvadersBodies;
        public System.Timers.Timer MoveTimer;
        public bool AtBottom;

        public Invaders()
        {
            X = 0;
            Y = 0;
            XDirection = 32;
            InvadersBodies = new Rectangle[Width * Height];
            MoveTimer = new();
            MoveTimer.Elapsed += new(Move);
            MoveTimer.Interval = 1000;
            MoveTimer.Enabled = true;
            AtBottom = false;

            for (int y = 0; y < Height; y++)
                for (int x = 0; x < Width; x++)
                    InvadersBodies[y * Width + x] = new(x * 32 + x * 32, y * 32 + y * 32, 32, 32);
        }

        public bool HasBulletHit(Rectangle bullet)
        {
            for (int i = 0; i < InvadersBodies.Length; i++)
            {
                if (InvadersBodies[i].IntersectsWith(bullet))
                {
                    InvadersBodies[i] = new(0, 0, 0, 0);
                    return true;
                }
            }

            return false;
        }

        public void Move(object? sender, ElapsedEventArgs e)
        {
            if (Y == (21 - 5) * 32)
            {
                AtBottom = true;
                return;
            }

            if (X == 8 * 32 || (X - 32 < 0 && XDirection == -32))
            {
                Y += 32;
                XDirection = -XDirection;
            }

            X += XDirection;
            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {
                    InvadersBodies[y * Width + x].X = X + x * 32 + x * 32;
                    InvadersBodies[y * Width + x].Y = Y + y * 32 + y * 32;
                }
            }
        }
    }
}
