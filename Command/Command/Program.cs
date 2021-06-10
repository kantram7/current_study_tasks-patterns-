using System;
using System.Collections.Generic;

namespace Command
{
    interface ICommand
    {
        void Start();
        void Stop();
    }
    class Game
    {
        public void Start()
        {
            Console.WriteLine("Игра начата.");
        }

        public void Stop()
        {
            Console.WriteLine("Игра закончена.");
        }

    }
    class GameOnCommand : ICommand
    {
        Game g;
        public GameOnCommand(Game game)
        {
            g = game;
        }
        public void Start()
        {
            g.Start();
        }
        public void Stop()
        {
            g.Stop();
        }

    }

    class Unit
    {
        public const int min = 0;
        public const int max = 5;
        private int count;

        public Unit()
        {
            count = min;
        }

        public void SetNew()
        {
            if (count < max)
                count++;
            Console.WriteLine("На поле добавлен новый юнит. Количество юнитов: {0}", count);
        }
        public void DeleteOne()
        {
            if (count > min)
                count--;
            Console.WriteLine("Юнит удален с поля. Количество юнитов: {0}", count);
        }
    }

    class UnitOnCommand : ICommand
    {
        Unit u;
        public UnitOnCommand(Unit unit)
        {
            u = unit;
        }
        public void Start()
        {
            u.SetNew();
        }

        public void Stop()
        {
            u.DeleteOne();
        }
    }

    class NoCommand : ICommand
    {
        public void Start()
        {
        }
        public void Stop()
        {
        }
    }

    class Pult
    {
        ICommand[] buttons;
        Stack<ICommand> commandsHistory;

        public Pult()
        {
            buttons = new ICommand[2];
            for (int i = 0; i < buttons.Length; i++)
            {
                buttons[i] = new NoCommand();
            }
            commandsHistory = new Stack<ICommand>();
        }

        public void SetCommand(int number, ICommand com)
        {
            buttons[number] = com;
        }

        public void PressButton(int number)
        {
            buttons[number].Start();
            // добавляем выполненную команду в историю команд
            commandsHistory.Push(buttons[number]);
        }
        public void PressUndoButton()
        {
            if (commandsHistory.Count > 0)
            {
                ICommand undoCommand = commandsHistory.Pop();
                undoCommand.Stop();
            }
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            Game game = new Game();
            Unit volume = new Unit();
            Pult pult = new Pult();
            pult.SetCommand(0, new GameOnCommand(game));
            pult.SetCommand(1, new UnitOnCommand(volume));
            // начинаем игру
            pult.PressButton(0);
            // добавляем юнита на поле
            pult.PressButton(1);
            pult.PressButton(1);
            pult.PressButton(1);
            // удаляем юнита с поля
            pult.PressUndoButton();
            pult.PressUndoButton();
            pult.PressUndoButton();
            pult.PressUndoButton();

            Console.Read();
        }
    } 
}