namespace Good
{ 
 
    interface INPCFactory
    {
        /// <summary>
        /// Каждая конкретная фабрика должна реализовывать свой способ создания объекта
        /// </summary>
        /// <returns></returns>
        INPC Create();
    }
}
