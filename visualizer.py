import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Configura el port serial (ajusta '/dev/ttyUSB0' o 'COMX' o /dev/tty.usbmodemXXXX segons el sistema)
ser = serial.Serial('/dev/cu.usbmodem142301', 9600)  # Substitueix pel port correcte
ser.flush()

# Inicialitza les llistes per emmagatzemar les dades
nh3_data = []
h2s_data = []
co2_data = []
temp_data = []
humidity_data = []

# Configura la gràfica amb 5 subgràfics
fig, axs = plt.subplots(5, 1, figsize=(8, 12))


# Funció per actualitzar les dades i la gràfica
def update(frame):
    if ser.in_waiting > 0:
        # Llegeix la línia de dades del port serial
        line = ser.readline().decode('utf-8').rstrip()
        data = line.split(',')

        # Afegeix les dades llegides a les llistes
        nh3_data.append(float(data[0]))
        h2s_data.append(float(data[1]))
        co2_data.append(float(data[2]))
        temp_data.append(float(data[3]))
        humidity_data.append(float(data[4]))

        # Mostra les darreres 50 dades
        nh3_data_plot = nh3_data[-50:]
        h2s_data_plot = h2s_data[-50:]
        co2_data_plot = co2_data[-50:]
        temp_data_plot = temp_data[-50:]
        humidity_data_plot = humidity_data[-50:]

        # Neteja les gràfiques
        for ax in axs:
            ax.cla()

        # Gràfica NH3
        axs[0].plot(nh3_data_plot, label='NH3 (ppm)', color='blue')
        axs[0].set_title('NH3 Concentració')
        axs[0].set_ylabel('NH3 (ppm)')
        axs[0].legend()

        # Gràfica H2S
        axs[1].plot(h2s_data_plot, label='H2S (ppm)', color='green')
        axs[1].set_title('H2S Concentració')
        axs[1].set_ylabel('H2S (ppm)')
        axs[1].legend()

        # Gràfica CO2
        axs[2].plot(co2_data_plot, label='CO2 (ppm)', color='red')
        axs[2].set_title('CO2 Concentració')
        axs[2].set_ylabel('CO2 (ppm)')
        axs[2].legend()

        # Gràfica Temperatura
        axs[3].plot(temp_data_plot, label='Temperatura (°C)', color='orange')
        axs[3].set_title('Temperatura')
        axs[3].set_ylabel('°C')
        axs[3].legend()

        # Gràfica Humitat
        axs[4].plot(humidity_data_plot, label='Humitat (%)', color='purple')
        axs[4].set_title('Humitat')
        axs[4].set_ylabel('%')
        axs[4].legend()

    plt.tight_layout()


# Crea una animació de les dades en temps real
ani = FuncAnimation(fig, update, interval=2000)

# Mostra la gràfica
plt.show()
