using System;
using System.Linq;
using Good.GameObjects;

namespace Good
{
    /// <summary>
    /// Класс представляющий локацию
    /// </summary>
    class Park
    {
        /// <summary>
        /// Монстры, обитающие на локации
        /// </summary>
        private INPC[] nPCs;
        
        /// <summary>
        /// Деревья на локации 
        /// </summary>
        private Tree[] trees;

        
        private Bench[] benches;

        public Park(INPC[] nPCs, Tree[] trees, Bench[] benches)
        {
            this.nPCs = nPCs;
            this.trees = trees;
            this.benches = benches;
        }

        
        public void NPCInfo()
        {
            var murlock = nPCs.Where((item) => {
                return item.ToString() == "Мурлок";
            }).Count();

            Console.WriteLine($"{murlock} Мурлок");


            var ogre = nPCs.Where((item) => {
                return item.ToString() == "Огр";
            }).Count();

            Console.WriteLine($"{ogre} Огр");


            var demon = nPCs.Where((item) => {
                return item.ToString() == "Демон";
            }).Count();

            Console.WriteLine($"{demon} Демон");
        }
       
    }
}
