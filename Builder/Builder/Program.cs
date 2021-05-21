using System;
using System.Collections.Generic;

namespace Builder
{
    class Unit
    {
        public string Unit_name { get; set; }
        public string Unit_class { get; set; }
        public int Atack { get; set; }
        public int Defence { get; set; }
        public int Price { get; set; }
        public bool Can_clone { get; set; }
        public bool Can_heal { get; set; }
        public override string ToString()
        {
            return Unit_name.ToString() + ": \nкласс: " + Unit_class.ToString() + ", атака: " + Atack.ToString() + ", защита: " + Defence.ToString() + ", цена: " + Price.ToString() + ", клонирование: " + Can_clone.ToString() + ", лечение: " + Can_heal.ToString();
        }
    }

    abstract class Unit_Builder : Unit
    {
        protected Unit unit;
        public Unit GetUnit()
        {
            return unit;
        }
        public void CreateNewUnit()
        {
            unit = new Unit();
        }
        public abstract void Name();
        public abstract void States();
    }

    class Soldier_Builder : Unit_Builder
    {
        public override void Name()
        {
            unit.Unit_name = "Пехотинец";
        }
        public override void States()
        {
            unit.Unit_class = "легкий";
            unit.Atack = 1;
            unit.Defence = 1;
            unit.Price = 1;
            unit.Can_clone = true;
            unit.Can_heal = true;
        }

    }
    class Archer_Builder : Unit_Builder
    {
        public override void Name()
        {
            unit.Unit_name = "Лучник";
        }
        public override void States()
        {
            unit.Unit_class = "легкий";
            unit.Atack = 1;
            unit.Defence = 1;
            unit.Price = 3;
            unit.Can_clone = true;
            unit.Can_heal = true;
        }

    }
    class Wizard_Builder : Unit_Builder
    {
        public override void Name()
        {
            unit.Unit_name = "Маг";
        }
        public override void States()
        {
            unit.Unit_class = "легкий";
            unit.Atack = 3;
            unit.Defence = 3;
            unit.Price = 5;
            unit.Can_clone = false;
            unit.Can_heal = false;
        }

    }

    class Director
    {
        private Unit_Builder builder;
        public void SetSoldier()
        {
            this.builder = new Soldier_Builder();
        }
        public void SetArcher()
        {
            this.builder = new Archer_Builder();
        }
        public void SetWizard()
        {
            this.builder = new Wizard_Builder();
        }
        public Unit GetUnit()
        {
            return builder.GetUnit();
        }
        public void BuildUnit()
        {
            builder.CreateNewUnit();
            builder.Name();
            builder.States();
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Director d = new Director();
            d.SetSoldier();
            d.BuildUnit();
            Unit unitS = d.GetUnit();
            Console.WriteLine(unitS.ToString());
            d.SetArcher();
            d.BuildUnit();
            Unit unitA1 = d.GetUnit();
            Console.WriteLine(unitA1.ToString());
            Unit unitA2 = d.GetUnit();
            Console.WriteLine(unitA2.ToString());
            d.SetWizard();
            d.BuildUnit();
            Unit unitW = d.GetUnit();
            Console.WriteLine(unitW.ToString());
        }
    }
}