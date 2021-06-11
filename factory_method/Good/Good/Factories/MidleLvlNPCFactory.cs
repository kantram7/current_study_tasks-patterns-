using Good.NPC;

namespace Good.Factories
{ 
   
    class MidleLvlNPCFactory : INPCFactory
    {
        private static int HardNPCCount = 0;

        public INPC Create()
        {
            if(HardNPCCount < 10) // проверяем созданы ли 10 сильных мобов
            {
                HardNPCCount += 1;
                return new Demon(); // если нет, то создаём
            }

            // если 10 сильных врагов созданы, то генерируем остальных рандомно
            INPCFactory ezFactory = new EzLvlNPCFactory();
            return ezFactory.Create();
        }

        public override string ToString() // реализуем приведение экземпляра класс к строке
        {
            return "Средний уровень сложности";
        }
    }
}
