using System;
using Good.GameObjects;

namespace Good
{
    
    class Game
    {
        private Park location;
        private Hero gamer;

        public Game(INPCFactory factory)
        {
            gamer = new Hero(); // В игре должен быть главный герой, за которого бы будем играть

            Tree[] trees = new Tree[] { // Задаём список деревьев, которые будут на локации
                new Tree(),
                new Tree(),
                new Tree()
            };

            Bench[] benches = new Bench[] { 
                new Bench(),
                new Bench(),
                new Bench()
            };

            INPC[] nPCs = new INPC[100]; // Задаём список монстров на локации

            for(int i = 0; i < nPCs.Length; i++)
            {
                nPCs[i] = factory.Create(); // заполнение массива делегировано фабричному методу
            }

            location = new Park(nPCs, trees, benches); // инициализируем игровую локацию

            
        }

        
        public void StartGame()
        {
            Console.WriteLine("Локация загружена");
            Console.WriteLine("Деревья расставлены");
            Console.WriteLine("Скамейки расставлены");
            Console.WriteLine("Монстры на местах");
            Console.WriteLine("Игрок загружен");
            Console.WriteLine("И тут игра, такая, начинается");

            location.NPCInfo();  

        }
    }
}
