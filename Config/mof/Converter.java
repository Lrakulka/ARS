package com.borysov.converter;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * This Converter convert pos animation files into pos files

 * Author Oleksandr Borysov
 * Date 19.11.2016
 **/

public class Converter {
    public static final String POS_FILES = ".pos";
    public static final String POS_START_CONFIG = "#";
    public static final String POS_START_STIFFNESS = "$";
    public static final String MOF_FILES = ".mof";
    public static final String MOF_FILE_CONFIG = "\t\t\"\t\tHY\t\tHP\t\tLSP\t\tLSR\t\tLEY\t\tLER\t\t_LWY_\t\t_LH_\t\tRSP\t\tRSR\t\tREY\t\tRER\t\t_RWY_\t\t_RH_\t\tLHYP\t\tLHR\t\tLHP\t\tLKP\t\tLAP\t\tLAR\t\tRHYP\t\tRHR\t\tRHP\t\tRKP\t\tRAP\t\tRAR\t\tInt\t\tDur";
    public static final String MOF_DEFAULT_CONFIG = "-";
    public static final String MOF_DEFAULT_STIFFNESS = "0";  // was *
    public static final String MOF_STIFFNESS = "stiffness";
    public static final String MOF_SEPARATOR = "\t\t";
    public static final String MOF_DEFAULT_INT = "1";
    
    public static final String[] MOF_SEQUENCE = "HY HP LSP LSR LEY LER LWY LH RSP RSR REY RER RWY RH LHYP LHR LHP LKP LAP LAR RHYP RHR RHP RKP RAP RAR Int Dur".split("[\\s()]+");
    public static final String[] POS_SEQUENCE = "HY HP LSP LSR LEY LER LWY LH LHYP LHR LHP LKP LAP LAR RHR RHP RKP RAP RAR RSP RSR REY RER RWY RH DUR".split("[\\s()]+");
    public static int[] map = new int[MOF_SEQUENCE.length];

    public static void main(String[] args) {
        String fileName;
        File[] files = new File("./").listFiles((f) -> {
            return f.getName().contains(POS_FILES);
        });
        buildMap();
        for (File posFile : files) {
            fileName = posFile.getName().substring(0, posFile.getName().lastIndexOf("."));
            System.out.println("Converting file " + fileName);
            try {
                createMof(convert(getPOSdata(posFile), fileName), fileName + MOF_FILES);
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("Converting error file " + fileName);
            }
        }
    }

    private static void buildMap() {
        for (int i = 0; i < MOF_SEQUENCE.length; i++) {
            map[i] = -1;
            for (int j = 0; j < POS_SEQUENCE.length; j++) {
                if (MOF_SEQUENCE[i].equalsIgnoreCase(POS_SEQUENCE[j])) {
                    map[i] = j;
                    break;
                }
            }
        }
    }

    private static List<String> convert(List<String> posData, String animationName) {
        List<String> curLine;
        List<String> mofData = new ArrayList<>();
        mofData.add("motion_id = " + animationName);
        mofData.add("\"Animation converted from pos file");
        mofData.add("");
        mofData.add("label start");
        mofData.add(MOF_FILE_CONFIG);
        for (int i = 1; i < posData.size(); ++i) {
            curLine = Arrays.asList(posData.get(i).split("[\\s()]+"));
            if (curLine.size() > 2) {   // Dumb protection
                if (curLine.get(0).contains(POS_START_CONFIG)) {
                    mofData.add("\"" + posData.get(i) + "\"");
                } else if (curLine.get(0).contains(POS_START_STIFFNESS)) {
                    mofData.add(addStinffness(curLine));
                } else {
                        mofData.add(addConfig(curLine));
                }
            }
        }
        mofData.add("");
        mofData.add("transition allMotions extern start");
        return mofData;
    }

    private static String addConfig(List<String> curLine) {
        StringBuffer line = new StringBuffer();
        line.append(MOF_SEPARATOR).append(MOF_SEPARATOR);
        for (int i = 0; i < map.length; ++i) {
            if (map[i] == -1) {
                if (i == map.length - 2)  {
                    line.append(MOF_DEFAULT_INT);
                } else {
                    line.append(MOF_DEFAULT_CONFIG);
                }
            } else {
                try {
                    line.append(curLine.get(map[i] + 1));
                } catch (Exception e) {
                    System.out.print("dfgv");
                }
            }
            line.append(MOF_SEPARATOR);
        }
        return line.toString();
    }

    private static String addStinffness(List<String> curLine) {
        StringBuffer line = new StringBuffer(MOF_STIFFNESS);
        line.append(MOF_SEPARATOR);
        for (int i = 0; i < map.length - 1; ++i) {
            if (map[i] == -1) {
                line.append(MOF_DEFAULT_STIFFNESS);
            } else {
                if (curLine.get(1 + map[i]).equals("-1")) {
                  line.append("-1");
                } else {
                    line.append(String.valueOf((int) (Float.valueOf(curLine.get(1 + map[i])) * 100)));
                }
            }
            line.append(MOF_SEPARATOR);
        }
        return line.toString();
    }

    private static void createMof(List<String> mofData, String mofName) {
        BufferedWriter bw = null;
        try {
            bw = new BufferedWriter(new FileWriter(mofName));
            for (String line: mofData) {
                bw.write(line);
                bw.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (bw != null) bw.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

    private static List<String> getPOSdata(File posFile) {
        List<String> data = new ArrayList<>();
        BufferedReader br = null;
        String posCurrentLine;
        try {
            br = new BufferedReader(new FileReader(posFile));
            while ((posCurrentLine = br.readLine()) != null) {
                data.add(posCurrentLine);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (br != null) br.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
        return data;
    }
}
