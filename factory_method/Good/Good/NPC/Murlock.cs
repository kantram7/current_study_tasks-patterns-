using System;

namespace Good.NPC
{
    class Murlock : INPC
    {
        public void BatleRoar()
        {
            Console.WriteLine("МРГЛБРГЛ");
        }

        public override string ToString()
        {
            return "Мурлок"; 
        }
    }
}
