using System;

using Good.NPC;

namespace Good.Factories
{
    
    class HardLvlNPCFactory : INPCFactory
    {
        private static Random rnd = new Random();
        public INPC Create()
        {
            string[] npc = new string[] {
                "Огр",
                "Демон"
            };

            switch (npc[rnd.Next(0, npc.Length)]) 
            {
                case "Огр":
                    return new Ogre();
                case "Демон":
                    return new Demon();
                default:
                    throw new Exception("Таких конкретных классов нет D:");
            }
        }

        public override string ToString() 
        {
            return "Сложный уровень сложности";
        }
    }
}
