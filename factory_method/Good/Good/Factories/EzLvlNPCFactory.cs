using System;

using Good.NPC;

namespace Good.Factories
{
    
    class EzLvlNPCFactory : INPCFactory
    {
        private static Random rnd = new Random();

        public INPC Create()
        {
            string[] npc = new string[] {
                "Мурлок",
                "Огр",
                "Демон"
            };

            switch(npc[rnd.Next(0, npc.Length)]) // Рандомно выбираем из всех
            {
                case "Мурлок":
                    return new Murlock();
                case "Огр":
                    return new Ogre();
                case "Демон":
                    return new Demon();
                default:
                    throw new Exception("Таких конкретных классов нет D:");
            }
        }

        public override string ToString() // реализуем приведение экземпляра класс к строке
        {
            return "Лёгкий уровень сложности";
        }
    }
}
