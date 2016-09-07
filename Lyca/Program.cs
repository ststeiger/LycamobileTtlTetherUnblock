
namespace Lyca
{


    static class Program
    {


        static void SetDefaultTtl()
        {
            const string PROCFS_IPV4_TTL = "/proc/sys/net/ipv4/ip_default_ttl";

            //Windows Registry Editor Version 5.00
            // [HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\servic es\Tcpip\Parameters]
            // "DefaultTTL"=dword:00000081

            if (System.IO.File.Exists(PROCFS_IPV4_TTL))
            {
                try
                {
                    string oldTTL = System.IO.File.ReadAllText(PROCFS_IPV4_TTL, System.Text.Encoding.UTF8);
                    System.Console.WriteLine("Old default ttl: {0}", oldTTL);

                    System.IO.File.WriteAllText(PROCFS_IPV4_TTL, "85", System.Text.Encoding.UTF8);
                    string newTTL = System.IO.File.ReadAllText(PROCFS_IPV4_TTL, System.Text.Encoding.UTF8);
                    System.Console.WriteLine("New default ttl: {0}", newTTL);
                }
                catch (System.Exception ex)
                {
                    System.Console.WriteLine("Setting TTL failed. Reason: ");
                    System.Console.WriteLine(ex.Message);
                    System.Console.WriteLine(System.Environment.NewLine);
                }
                
            }
            else
                System.Console.WriteLine("ProcFS file not found...");
        } // End Sub SetDefaultTtl 


        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [System.STAThread]
        static void Main()
        {
            SetDefaultTtl(); 

            if (false)
            {
                System.Windows.Forms.Application.EnableVisualStyles();
                System.Windows.Forms.Application.SetCompatibleTextRenderingDefault(false);
                System.Windows.Forms.Application.Run(new Form1());
            } // End if (false) 

        } // End Sub Main 


    } // End Class Program 


} // End Namespace Lyca
