namespace TextMovement
{
    internal class Program
    {
        static void Main(string[] args)
        {
            const int _roomWidth = 20;
            const int _roomHeight = 10;
            const int _roomPadding = 2;

            int _playerX = 0;
            int _playerY = 0;

            ConsoleKeyInfo key = new ConsoleKeyInfo();
            
            while (key.Key != ConsoleKey.Q)
            {
                key = Console.ReadKey(true);
                switch (key.Key)
                {
                    case ConsoleKey.W:
                        if (_playerY > 0)
                            _playerY--;
                        break;
                    case ConsoleKey.S:
                        if (_playerY < _roomHeight)
                            _playerY++;
                        break;
                    case ConsoleKey.A:
                        if (_playerX > 0)
                            _playerX--;
                        break;
                    case ConsoleKey.D:
                        if (_playerX < _roomWidth)
                            _playerX++;
                        break;
                }

                Console.SetWindowSize(_roomWidth + _roomPadding, _roomHeight + _roomPadding);
                Console.ResetColor();
                Console.Clear();
                for (int y = 0; y < _roomHeight; y++)
                {
                    for (int x = 0; x < _roomWidth; x++)
                    {
                        if (x == _playerX && y == _playerY)
                        {
                            Console.BackgroundColor = ConsoleColor.Red;
                            Console.SetCursorPosition(_playerX + _roomPadding, _playerY + _roomPadding);
                        }
                        else
                        {
                            Console.BackgroundColor = ConsoleColor.Blue;
                            Console.SetCursorPosition(x + _roomPadding, y + _roomPadding);
                        }

                        Console.Write(" ");
                    }
                }
            }



        }
    }
}
