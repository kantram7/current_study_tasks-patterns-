using System;
using System.Collections.ObjectModel;

namespace Vizitor
{
    class Program
    {
        interface IVisitor
        {
            void SetArcher(Archer car);
            void SetWizard(Wizard track);
        }
        class Setter : IVisitor
        {
            public void SetArcher(Archer a)
            {
                Console.WriteLine($"Здоровье лучника: {a.Health}. Атака лучника: {a.Atack}");
            }
            public void SetWizard(Wizard w)
            {
                Console.WriteLine($"Здоровье мага: {w.Health}. Атака мага: {w.Atack}");
            }
        }
        abstract class Mob
        {
            public int Health { get; set; }
            public int Atack { get; set; }
            public abstract void Set(IVisitor visitor);
        }
        class Archer : Mob
        {
            public override void Set(IVisitor visitor)
            {
                visitor.SetArcher(this);
            }
        }
        class Wizard : Mob
        {
            public override void Set(IVisitor visitor)
            {
                visitor.SetWizard(this);
            }
        }
        static void Main(string[] args)
        {
            Collection<Mob> collection = new Collection<Mob>
            {
                new Archer { Health = 5, Atack = 5 },
                new Wizard { Health = 15, Atack = 5 },
                new Archer { Health = 5, Atack = 15 },
                new Wizard { Health = 15, Atack = 15 }
            };
            IVisitor visitor = new Setter();
            foreach (Mob m in collection)
            {
                m.Set(visitor);
            }
        }
    }
}
