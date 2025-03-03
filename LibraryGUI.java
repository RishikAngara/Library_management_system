import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LibraryGUI {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Library Management System");
        frame.setSize(500, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());

        JLabel label = new JLabel("Library Management System", SwingConstants.CENTER);
        label.setFont(new Font("Arial", Font.BOLD, 16));
        panel.add(label, BorderLayout.NORTH);

        JTextArea textArea = new JTextArea();
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);
        panel.add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        JButton viewBooksButton = new JButton("View Books");
        JButton addBookButton = new JButton("Add Book");
        JButton issueBookButton = new JButton("Issue Book");

        buttonPanel.add(viewBooksButton);
        buttonPanel.add(addBookButton);
        buttonPanel.add(issueBookButton);
        panel.add(buttonPanel, BorderLayout.SOUTH);

        frame.add(panel);
        frame.setVisible(true);

        // Event Handlers
        viewBooksButton.addActionListener(e -> new Thread(() -> {
            textArea.setText(runCommand("library_cpp.exe", "2"));  // Calls C++ code to display books
        }).start());

        addBookButton.addActionListener(e -> new Thread(() -> {
            String bookID = JOptionPane.showInputDialog("Enter Book ID:");
            String title = JOptionPane.showInputDialog("Enter Book Title:");
            String author = JOptionPane.showInputDialog("Enter Author:");
            runCommand("library_cpp.exe", "1", bookID, title, author);
            JOptionPane.showMessageDialog(frame, "Book added successfully!");
        }).start());

        issueBookButton.addActionListener(e -> new Thread(() -> {
            String bookID = JOptionPane.showInputDialog("Enter Book ID to Issue:");
            runCommand("library_cpp.exe", "3", bookID);
            JOptionPane.showMessageDialog(frame, "Book issued successfully!");
        }).start());
    }

    private static String runCommand(String... command) {
        try {
            ProcessBuilder pb = new ProcessBuilder(command);
            Process process = pb.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();
            return output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing command.";
        }
    }
}
