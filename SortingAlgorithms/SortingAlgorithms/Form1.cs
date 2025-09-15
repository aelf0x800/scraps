namespace SortingAlgorithms
{
    public partial class Form1 : Form
    {
        private Random _random;
        private int[] _data;
        private int _delay;
        private Thread _searchThread;

        public Form1()
        {
            InitializeComponent();

            Name = "Searching algorithms";
            Text = "Searching algorithms";
            Size = new(1920, 1080);
            MinimumSize = new(300, 300);
            DoubleBuffered = true;
            BackColor = Color.Black;
            Paint += Form1_Paint;
            KeyDown += Form1_KeyDown;
            Resize += Form1_Resize;
            FormClosed += Form1_FormClosed;

            _random = new();
            _data = new int[300];
            _delay = 5;
            _searchThread = new(BubbleSort);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < _data.Length; i++)
            {
                _data[i] = _random.Next(1, 300);
            }

            _searchThread.Start();
        }

        private void Form1_KeyDown(object? sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Up:
                    _delay = _delay + 5 > 100 ? 100 : _delay + 2;
                    break;
                case Keys.Down:
                    _delay = _delay - 5 < 0 ? 0 : _delay - 2;
                    break;
            }

            Invalidate();
        }

        private void Form1_Paint(object? sender, PaintEventArgs e)
        {
            e.Graphics.Clear(Color.Black);

            for (int i = 0; i < _data.Length; i++)
            {
                int width = Convert.ToInt32(Width / _data.Length);
                int height = Convert.ToInt32((_data[i] / 300.0) * Height);
                e.Graphics.FillRectangle(Brushes.Green, new(width * i, Height - height, width, height));
            }

            string infoString = $"""
                                Values: {_data.Length}
                                Delay: {_delay}
                                """;
            e.Graphics.DrawString(infoString, Font, Brushes.White, 0, 0);

        }
        private void Form1_Resize(object? sender, EventArgs e) => Invalidate();
        private void Form1_FormClosed(object? sender, FormClosedEventArgs e) => _searchThread.Join();

        private void BubbleSort()
        {
            bool swapOccured = true;
            for (int i = 0; i < _data.Length && swapOccured; i++)
            {
                swapOccured = false;
                for (int j = 0; j < _data.Length - 1; j++)
                {
                    if (_data[j] > _data[j + 1])
                    {
                        (_data[j + 1], _data[j]) = (_data[j], _data[j + 1]);
                        swapOccured = true;

                        Invalidate();
                        Thread.Sleep(_delay);
                    }
                }
            }
        }
    }
}
