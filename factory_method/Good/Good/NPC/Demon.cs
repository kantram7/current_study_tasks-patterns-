using System;

namespace Good.NPC
{
    class Demon : INPC
    {
        public void BatleRoar()
        {
            Console.WriteLine("Ты уже мёртв, смертный");
        }

        public override string ToString()
        {
            return "Демон";
        }
    }
}
