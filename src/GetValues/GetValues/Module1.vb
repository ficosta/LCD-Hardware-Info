Imports System.Threading
Imports System.Diagnostics

Public Class TestPerfCounter
    Shared memory_total As Integer = System.Math.Round(My.Computer.Info.TotalPhysicalMemory / (1024 * 1024))
    Shared memory_available As Integer
    Shared cpu_used As New System.Diagnostics.PerformanceCounter("Processor", "% Processor Time", "_Total", True)


    Public Shared Sub Main()
      
        While True

            Console.WriteLine(CInt(cpu_used.NextValue) & " --- " & CInt((100 * (memory_total - System.Math.Round(My.Computer.Info.AvailablePhysicalMemory / (1024 * 1024))) / memory_total)))
            Threading.Thread.Sleep(1000)

        End While
    End Sub
End Class